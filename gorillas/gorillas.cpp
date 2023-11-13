#include <duels/gorillas/game.h>

using namespace duels::gorillas;

int main(int argc, char** argv)
{
  Game game(argc, argv, "Your name here", 3);   // difficulty from 0 to 3

  Input input;
  Feedback feedback;
  const auto timeout = game.timeout_ms();

  while(game.get(feedback))
  {    
    // write input in less than timeout
    input.angle = 60;
    input.vel = 50;

    game.send(input);


  }
}
