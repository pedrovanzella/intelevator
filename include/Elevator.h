#pragma once

#include <map>
#include <queue>
#include <set>
#include "Client.h"
#include "Direction.h"
#include "Floor.h"

class Elevator {
public:
  Floor currentFloor;
  std::queue<Floor*> destinations;
  std::map<Floor*, std::set<Client*>> passengers;

  Elevator();
  Direction direction();
  int occupation();
};