#pragma once

#include <queue>
#include <map>
#include <set>
#include "floor.h"
#include "client.h"
#include "direction.h"

class Elevator {
public:
  Floor currentFloor;
  std::queue<std::shared_ptr<Floor>> destinations;
  std::map<std::shared_ptr<Floor>, std::set<std::shared_ptr<Client>>> passengers;

  Direction direction();
  int occupation();
};