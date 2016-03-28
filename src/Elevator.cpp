#include <memory>
#include "Elevator.h"

Elevator::Elevator(const std::shared_ptr<const Building> building)
  : _building(building)
{
    _current_floor = _building->getLobby();
}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

double Elevator::getOccupation() const
{
  if (_building->getConfig()->getInt(Property::MaxLoad) == 0) return 0.0;

  int total_passengers = 0;
  for (auto const& client : _passengers)
  {
    total_passengers += client->getPartySize();
  }
  return total_passengers / _building->getConfig()->getInt(Property::MaxLoad);
}

void Elevator::addPassenger(std::shared_ptr<const Client> client)
{
  _passengers.insert(client);
}

std::shared_ptr<std::set<const Floor>> Elevator::getDestinations() const
{
  std::shared_ptr<std::set<const Floor>> floors;

  // for (auto client : _passengers) {
  //   floors->insert(client.getDestination());
  // }

  return floors;
}

std::shared_ptr<const Floor> Elevator::getCurrentFloor() const
{
    return _current_floor;
}
