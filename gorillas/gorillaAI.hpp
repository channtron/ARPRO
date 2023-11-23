#ifndef GORILLAAI_HPP
#define GORILLAAI_HPP

#include <iostream>
#include <string>
#include <vector>

#include <duels/gorillas/msg.h>

using namespace duels::gorillas;

struct gorillaAi {
    gorillaAi(){}
    // compute next game input from current feedback from the game
    Input computeFrom(const Feedback &feedback){
        Input input;
        if (feedback.banana.x==0){
            auto noBuilding{true};
            auto me{feedback.me};
            auto op{feedback.opponent};
            auto m = (me.y-op.y)/(me.x-op.x);
            auto b = me.y-m*(me.x+3);
            for (auto i = me.x; i< op.x; i++){
                auto h = feedback.building[i];
                auto maxHAllow = m*i+b;
                if (h > maxHAllow) noBuilding = false;
            }
            if (noBuilding){
                input.angle = atan2(op.y-me.y,op.x-me.x)*180/M_PI;
                input.vel = 1000;
            } else {
                input.angle = m_lastAngle;
                input.vel = m_lastVel;
            }
        } else {
            duels::Vector2D<int> banana {int(feedback.banana.x),int(feedback.banana.y)};
            auto xError = feedback.opponent.x-feedback.banana.x;
            auto yError = feedback.opponent.y-feedback.banana.y;
            auto yBananaError = feedback.building[banana.x]-banana.y;
            if (banana.y < feedback.building[banana.x])
            {
                auto angleBanana = atan2(banana.y-feedback.me.y,banana.x-feedback.me.x)*180/M_PI;
                auto angleBuilding = atan2(feedback.building[banana.x]-feedback.me.y,banana.x-feedback.me.x)*180/M_PI;
                std::cout << "Banana: " << banana.x << ',' << banana.y << "\tbuildin: " << feedback.building[banana.x] << "\tme :"<< feedback.me.x << ',' << feedback.me.y << std::endl;

                m_lastAngle = m_lastAngle + (angleBuilding-angleBanana);//;

                if (m_lastAngle >= 80) m_lastAngle = 80;
                if (m_lastAngle <= 30) m_lastAngle = 30;

            } else {
                m_xErrorI += xError;


                m_lastVel = m_lastVel + 0.3*xError+ 0.03*m_xErrorI + 0.02*(xError-m_Error1);
                m_lastAngle = m_lastAngle ;//- 1*yError;

                if (m_xErrorI >= 300) m_xErrorI = 300;
                if (m_xErrorI <= -200) m_xErrorI = -200;

                if (m_lastVel >= 250) m_lastVel = 250;
                if (m_lastVel <= 15) m_lastVel = 15;
                m_Error1 = xError;

            }
            std::cout << "Vel: " << m_lastVel << ",\tAngle: " << m_lastAngle << ",\txError: " << xError << ",\tInt: " << m_xErrorI << std::endl;
            input.angle = m_lastAngle;
            input.vel = m_lastVel;
        }
        return input;
    }
    float m_lastAngle = 50;
    float m_lastVel = 50;
    float m_Error1 = 0;
    float m_xErrorI = 0;
};


#endif // GORILLAAI_HPP
