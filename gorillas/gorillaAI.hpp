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
            input.angle = m_lastAngle;
            input.vel = m_lastVel;
        } else {
            duels::Vector2D<int> banana {int(feedback.banana.x),int(feedback.banana.y)};

            auto xError = feedback.opponent.x-feedback.banana.x;
            auto yError = feedback.opponent.y-feedback.banana.y;
            m_xErrorI += xError;

            m_lastVel = m_lastVel + 0.3*xError+ 0.05*m_xErrorI;
            m_lastAngle = m_lastAngle ;//- 1*yError;
            std::cout << "Vel: " << m_lastVel << ",\tAngle: " << m_lastAngle << ",\txError: " << xError << ",\tInt: " << m_xErrorI << std::endl;

            if (m_lastVel >= 250) m_lastVel = 250;
            if (m_lastVel <= 15) m_lastVel = 15;

            if (m_lastAngle >= 80) m_lastAngle = 80;
            if (m_lastAngle <= 30) m_lastAngle = 30;
            input.angle = m_lastAngle;
            input.vel = m_lastVel;
        }
        return input;
    }
    float m_lastAngle = 50;
    float m_lastVel = 50;

    float m_xErrorI = 0;
};


#endif // GORILLAAI_HPP
