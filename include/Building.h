#pragma once

#include <list>
#include <set>
#include "Config.h"
#include "Elevator.h"
#include "Floor.h"

class Building {
private:
  std::set<Elevator> elevators;
  std::list<Floor> floors;

public:
  void reset(Config& config);
};