#pragma once

#include <set>
#include <list>
#include "elevator.h"
#include "floor.h"
#include "config.h"

class Building {
private:
  std::set<Elevator> elevators;
  std::list<Floor> floors;

public:
  void reset(std::shared_ptr<Config> config);
};