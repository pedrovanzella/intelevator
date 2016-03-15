#pragma once

#include <list>
#include <map>
#include <set>
#include "Config.h"
#include "EventObserver.h"

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building : public EventObserver
{
public:
  Building(Config& config);
  virtual ~Building();

  void notify(const Event& event) const;

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
