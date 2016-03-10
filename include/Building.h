#pragma once

#include <list>
#include <set>
#include "Config.h"

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building {
private:
  Config& config;

  std::list<Elevator*> elevators;
  std::list<Floor*> floors;

public:
  Building(Config&);
  virtual ~Building();

  void reset(Config&);
  const Config& getConfig();
};