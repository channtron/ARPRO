#include <duels/gorillas/game.h>
#include "gorillaAI.hpp"

using namespace duels::gorillas;

int main(int argc, char** argv)
{
    auto level{0};
    if (argc>1) level = *argv[1];
  Game game(argc, argv, "Your name here", level);   // difficulty from 0 to 3

  Input input;
  Feedback feedback;
  const auto timeout = game.timeout_ms();

  gorillaAi gorilla;
  while(game.get(feedback))
  {    
    // write input in less than timeout
    input = gorilla.computeFrom(feedback);
    /*
    input.angle = 60;
    input.vel = 50;
    */
    game.send(input);


  }
}
