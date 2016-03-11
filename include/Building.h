#pragma once

#include <list>
#include <map>
#include <set>
#include "Config.h"

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building {
private:
  Config& config;
  std::list<Elevator*> elevators;
  std::list<Floor*> floors;

  std::map<Elevator*, Floor*>locations;

public:
  Building(Config&);
  virtual ~Building();

  void reset(Config&);
  const Config& getConfig();

  const std::list<Elevator*>& getElevators();
  const std::list<Floor*>& getFloors();

  void setLocation(Elevator* elevator, Floor* location);
  Floor* getLocation(Elevator* elevator);
};