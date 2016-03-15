#include "Building.h"
#include "Elevator.h"
#include "Floor.h"

Building::Building(Config& config)
 : _config(config)
{
  Floor* f = nullptr;
  for (int i = 0; i < _config._floors; i++)
  {
    f = new Floor(i);
    _floors.push_back(f);
  }

  Floor* lobby = _floors.front();

  Elevator* e = nullptr;
  for (int i = 0; i < _config._elevators; i++)
  {
    e = new Elevator(_config);
    _elevators.push_back(e);
    setLocation(e, lobby);
  }
}

Building::~Building()
{
  Floor* f = nullptr;
  while(!_floors.empty())
  {
    f = _floors.back();
    _floors.pop_back();
    delete f;
  }

  Elevator* e = nullptr;
  while(!_elevators.empty())
  {
    e = _elevators.back();
    _elevators.pop_back();
    delete e;
  }
}

void Building::notify(const Event&) const
{
  // TO-DO
}

const Config& Building::getConfig() const
{
  return _config;
}

void Building::setLocation(Elevator* elevator, Floor* location)
{
  _locations[elevator] = location;
}

Floor* Building::getLocation(Elevator* elevator)
{
  return _locations[elevator];
}

const std::list<Elevator*>& Building::getElevators() const
{
  return _elevators;
}

const std::list<Floor*>& Building::getFloors() const
{
  return _floors;
}
