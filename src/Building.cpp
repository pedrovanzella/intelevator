#include "Building.h"
#include "Elevator.h"
#include "Floor.h"
#include "DummyDispatcher.h"

#include <iostream>
#include <memory>
#include <NearestNeighbourDispatcher.h>

Building::Building(const std::shared_ptr<const Config> config)
 : _config(config)
{
    auto dispatcher_name = config->getDispatcher();

    if (dispatcher_name == "Dummy") {
        _dispatcher = std::shared_ptr<DummyDispatcher>(new DummyDispatcher(*this));
    } else if (dispatcher_name == "NearestNeighbour") {
        _dispatcher = std::shared_ptr<NearestNeighbourDispatcher>(new NearestNeighbourDispatcher(*this));
    }
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

const std::list<std::shared_ptr<const Elevator>>& Building::getElevators() const
{
  return _elevators;
}

const std::list<std::shared_ptr<const Floor>>& Building::getFloors() const
{
  return _floors;
}

std::shared_ptr<const Floor> Building::getLobby() const
{
    auto lobby = _floors.front();

    // Floors might not be in order, for some freak reason
    if (lobby->getNumber() != 1) {
        for (auto floor : _floors) {
            if (floor->getNumber() == 1) {
                lobby = floor;
                break;
            }
        }
    }

    return lobby;
}
