#include "Building.h"
#include "Elevator.h"
#include "Floor.h"
#include "DummyDispatcher.h"

#include <iostream>
#include <memory>

Building::Building(const std::shared_ptr<const Config> config)
 : _config(config)
{
  _dispatcher = std::unique_ptr<DummyDispatcher>(new DummyDispatcher(this));
}

Building::~Building()
{
  _floors.clear();
  _elevators.clear();
}

void Building::build()
{
  for (int i = 0; i < _config->getFloors(); i++)
  {
    _floors.push_back(std::shared_ptr<Floor>(new Floor(i)));
  }

  auto lobby = _floors.front();
  std::shared_ptr<Building> building = std::static_pointer_cast<Building>(shared_from_this());
  for (int i = 0; i < _config->getElevators(); i++)
  {
    std::shared_ptr<Elevator> e(new Elevator(building));
    _elevators.push_back(e);
    setLocation(e, lobby);
  }
}

void Building::notify(const std::shared_ptr<const Event> event) const
{
  // TO-DO
}

const std::shared_ptr<const Config> Building::getConfig() const
{
  return _config;
}

void Building::setLocation(std::shared_ptr<const Elevator> elevator, std::shared_ptr<const Floor> location)
{
  _locations[elevator] = location;
}

const std::shared_ptr<const Floor> Building::getLocation(std::shared_ptr<const Elevator> elevator)
{
  return _locations[elevator];
}

const std::list<std::shared_ptr<const Elevator>>& Building::getElevators() const
{
  return _elevators;
}

const std::list<std::shared_ptr<const Floor>>& Building::getFloors() const
{
  return _floors;
}
