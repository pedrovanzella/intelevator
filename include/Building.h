#pragma once

#include <list>
#include <map>
#include <set>
#include "Config.h"

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building {
public:
  Building(Config& config);
  virtual ~Building();

  const Config& getConfig() const;

  void setLocation(Elevator* elevator, Floor* location);
  Floor* getLocation(Elevator* elevator);
  const std::list<Elevator*>& getElevators() const;
  const std::list<Floor*>& getFloors() const;

private:
  const Config& _config;
  std::list<Elevator*> _elevators;
  std::list<Floor*> _floors;
  std::map<Elevator*, Floor*> _locations;
};
