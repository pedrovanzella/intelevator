#include <algorithm>
#include <iostream>
#include <memory>

#include "Building.h"
#include "easylogging++.h"
#include "Elevator.h"
#include "Floor.h"

Building::Building(std::shared_ptr<std::vector<std::shared_ptr<const Floor>>> floors,
                   std::shared_ptr<std::vector<std::shared_ptr<const Elevator>>> elevators,
                   std::shared_ptr<const Dispatcher> dispatcher,
                   std::shared_ptr<const CostFunction> costFunction)
  : _floors(floors)
  , _elevators(elevators)
  , _dispatcher(dispatcher)
  , _costFunction(costFunction)
  {
    auto lobby = _floors->at(0);
    for (auto e : *_elevators)
    {
      setLocation(e, lobby);
    }
  }

Building::~Building() {}

void Building::notify(const std::shared_ptr<const Event> event)
{
  if (event->getType() == EventType::clientArrival)
  {
    auto elevator = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), std::static_pointer_cast<const ClientArrival>(event));
    // Do something with this elevator
  }
  // TO-DO
}

void Building::setLocation(std::shared_ptr<const Elevator> elevator, std::shared_ptr<const Floor> location)
{
  _locations[elevator] = location;
}

const std::shared_ptr<const Floor> Building::getLocation(std::shared_ptr<const Elevator> elevator)
{
  return _locations[elevator];
}

const std::shared_ptr<std::vector<std::shared_ptr<const Elevator>>> Building::getElevators() const
{
  return _elevators;
}

const std::shared_ptr<std::vector<std::shared_ptr<const Floor>>> Building::getFloors() const
{
  return _floors;
}

const std::shared_ptr<const Floor> Building::getFloor(int number) const
{
  if (number >= _floors->size()) throw std::out_of_range ("Floor number out of range: " + std::to_string(number));
  return _floors->at(number);
}

const std::shared_ptr<const Elevator> Building::getElevator(int number) const
{
  if (number >= _elevators->size()) throw std::out_of_range ("Elevator number our of range: " + std::to_string(number));
  return _elevators->at(number);
}
