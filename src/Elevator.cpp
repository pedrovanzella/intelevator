#include <memory>
#include "Elevator.h"

Elevator::Elevator(const std::shared_ptr<const Building> building)
  : _building(building) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

double Elevator::getOccupation() const
{
  if (_building->getConfig()->getMaxLoad() == 0) return 0.0;

  int total_passengers = 0;
  for (auto const& client : _passengers)
  {
      total_passengers += client->getPartySize();
  }
  return total_passengers / _building->getConfig()->getMaxLoad();
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
