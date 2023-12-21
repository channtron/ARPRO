#ifndef TREASUREHUNTAI_H
#define TREASUREHUNTAI_H

#include "boat_node.h"

class TreasureHuntAI
{
public:
  TreasureHuntAI();

  Action computeFrom(const Feedback &feedback,int verbose = 0);


private:
  BoatNode pose;
  Grid map;

  std::vector<Vector2D<int>> candidates;

  inline void removeCandidate(Vector2D<int> xy)
  {
    const auto pos = std::find(candidates.begin(), candidates.end(), xy);
    if(pos != candidates.end())
      candidates.erase(pos);
  }
  
  // erase-remove and exception from pruning candidates
  template <class Criterion>
  void pruneCandidates(const Criterion &crit)
  {
    candidates.erase(std::remove_if(candidates.begin(), candidates.end(), crit),
                     candidates.end());
    if(candidates.empty())
      throw std::out_of_range("pruneCandidates: No more treasure candidates: check your erase criterion");
  }

  // Added variables
  Orientation getNextOrientation(const BoatNode next);
  std::vector<std::vector<Orientation>> turnRight{{Orientation::UP,     Orientation::RIGHT},
                                                  {Orientation::RIGHT,  Orientation::DOWN},
                                                  {Orientation::DOWN,   Orientation::LEFT},
                                                  {Orientation::LEFT,   Orientation::UP}};

};

#endif // TREASUREHUNTAI_H
