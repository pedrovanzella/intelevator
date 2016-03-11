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

  Direction getDirection();
  int getOccupation();

private:
  std::queue<Floor*> destinations;
  std::map<Floor*, std::set<Client*>> passengers;
  int maxLoad;
};