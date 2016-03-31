#include <algorithm>
#include <iostream>
#include <memory>

#include "BetterNearestNeighbourDispatcher.h"
#include "Building.h"
#include "DummyDispatcher.h"
#include "easylogging++.h"
#include "Elevator.h"
#include "Floor.h"
#include "NearestNeighbourDispatcher.h"
#include "MissingDispatcherError.h"

Building::Building(const std::shared_ptr<const Config> config)
 : _config(config)
{
  LOG(TRACE) << "Building created.";
}

Building::~Building()
{
  _floors.clear();
  _elevators.clear();

  LOG(TRACE) << "Building destroyed.";
}

void Building::initialize()
{
  // Create building floors
  for (int i = 0; i < _config->getInt(Property::Floors); i++)
  {
    auto f = std::shared_ptr<Floor>(new Floor(i));
    _floors.push_back(f);
  }

  // Create building elevators and assign them to the lobby
  auto lobby = getLobby();
  std::shared_ptr<Building> building = std::static_pointer_cast<Building>(shared_from_this());
  for (int i = 0; i < _config->getInt(Property::Elevators); i++)
  {
    auto e = std::shared_ptr<Elevator>(new Elevator(building, i));
    _elevators.push_back(e);
    setLocation(e, lobby);
  }

  // Set up the building AI dispatcher
  auto dispatcher_name = _config->getString(Property::Dispatcher);
  if (dispatcher_name == "Dummy") {
    _dispatcher = std::shared_ptr<DummyDispatcher>(new DummyDispatcher(std::make_shared<Building>(*this)));
  } else if (dispatcher_name == "NearestNeighbour") {
    _dispatcher = std::shared_ptr<NearestNeighbourDispatcher>(new NearestNeighbourDispatcher(std::make_shared<Building>(*this)));
  } else if (dispatcher_name == "BetterNearestNeighbour") {
    _dispatcher = std::shared_ptr<BetterNearestNeighbourDispatcher>(new BetterNearestNeighbourDispatcher(std::make_shared<Building>(*this)));
  } else {
    throw MissingDispatcherError(dispatcher_name);
  }

  LOG(INFO) << "Building initialized with " << _floors.size() << " floors, " << _elevators.size() << " elevators and " << _config->getString(Property::Dispatcher) << " dispatcher.";
}

void Building::notify(const std::shared_ptr<const Event> event) const
{
  if (event->getType() == EventType::clientArrival) {
    auto elevator = _dispatcher->pick_next_elevator(std::static_pointer_cast<const ClientArrival>(event));
    // Do something with this elevator
  }
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

const std::vector<std::shared_ptr<const Elevator>>& Building::getElevators() const
{
  return _elevators;
}

const std::vector<std::shared_ptr<const Floor>>& Building::getFloors() const
{
  return _floors;
}

std::shared_ptr<const Floor> Building::getLobby() const
{
  return getFloor(0);
}

const std::shared_ptr<const Floor> Building::getFloor(int number) const
{
  if (number >= _floors.size()) throw std::out_of_range ("Floor number out of range: " + std::to_string(number));
  return _floors[number];
}

const std::shared_ptr<const Elevator> Building::getElevator(int number) const
{
  if (number >= _elevators.size()) throw std::out_of_range ("Elevator number our of range: " + std::to_string(number));
  return _elevators[number];
}
