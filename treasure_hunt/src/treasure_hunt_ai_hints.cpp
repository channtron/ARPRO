#include <treasure_hunt_ai_hints.h>
#include <duels/utils/grid_point.h>

#include <duels/algo/a_star.h>

constexpr int FREE{0};
constexpr int ROCK{1};
constexpr int UNKNOWN{2};

TreasureHuntAI::TreasureHuntAI()
  : map(20, 30, UNKNOWN) // fill the 20x30 map with 2's (unknown)
{
  // register this map for all grid points
  pose.setMap(map);

  // TODO the treasure may be at any position: update candidates
  for (int i{0}; i<20; i++) {
      for (int j{0}; j<30; j++){
          candidates.push_back({i,j});
      }
  }
}

//Orientation TreasureHuntAI::getNextOrientation(const BoatNode next)
//{
//    /*
//    if (next.x<pose.x) return Orientation::LEFT;
//    else if (next.x>pose.x) return Orientation::RIGHT;
//    else if (next.y<pose.y) return Orientation::UP;
//    else if (next.y>pose.y) return Orientation::DOWN;
//    */
//    if (next.x!=pose.x) {
//        if(next.x<pose.x)return Orientation::LEFT;
//        else return Orientation::RIGHT;
//    } else {
//        if(next.y<pose.y) return Orientation::UP;
//        else return Orientation::DOWN;
//    }
//}

Action TreasureHuntAI::computeFrom(const Feedback &feedback)
{
  // register where we are
  pose.set(feedback.pose);
  // if we are here then it is not a treasure position
  removeCandidate(pose);

  // TODO process feedback.scan to update map
  for(const auto &[x,y,rock]: feedback.scan)
  {
      map.cell(x,y) = rock;
  }

  // Function to process feedback.treasure_distance to update candidates
  // as we compare floating points, a smal-l threshold is useful to tell if two values are equal
  const auto threshold{0.8};
  //std::cout << "number of candidates: " << candidates.size() << std::endl;
  pruneCandidates([&](const Vector2D<int> &candidate)
  {
    // TODO return true if this candidate cannot be the treasure position
    auto distance = pose.distance(candidate);
//    auto distance = sqrt(pow(candidate.x-pose.x,2)+pow(candidate.y-pose.y,2));
    if((distance+threshold)>=feedback.treasure_distance
            && (distance-threshold)<=feedback.treasure_distance)
        return false;
    return true;
  });
  //std::cout << "number of candidates: " << candidates.size() << std::endl;

  // use A* to find shortest path to first candidate, will assume unknown cells are free
  const auto path{Astar(pose, candidates[0])};
  const auto next{path[1]};
  Action action{Action::SONAR}; // compute it from pose and next
  // TODO identify which move from pose to next

  if(map.cell(next) == UNKNOWN || map.cell(next) == ROCK) {
      action = Action::SONAR;
      return action;
  } else {
//      if (getNextOrientation(next) == pose.orientation) action = Action::MOVE;
      if (pose.forwardPosition() == next) action = Action::MOVE;
      else {
          action = Action::TURN_LEFT;
          for(const auto &orientations : turnRight){
              if (orientations[0] == pose.orientation && orientations[1] == next.orientation)
                  action = Action::TURN_RIGHT;
          }
          return action;
      }
  }
  // TODO do not use Action::MOVE if the next cell is unknown
  // if(map.cell(next) == UNKNOWN && ...)

  return action;
}
