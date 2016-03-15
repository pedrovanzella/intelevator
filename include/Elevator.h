#pragma once

#include <map>
#include <queue>
#include <set>
#include "Client.h"
#include "Config.h"
#include "Direction.h"

class Elevator {
public:
  Elevator(const Config& config);
  virtual ~Elevator();

  Direction getDirection() const;
  int getOccupation() const;

private:
  std::queue<Floor*> _destinations;
  std::map<Floor*, std::set<Client*>> _passengers;
  int _maxLoad;
};
