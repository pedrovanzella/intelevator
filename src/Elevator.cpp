#include "Elevator.h"

Elevator::Elevator(const Config& config, const Building* building)
  : _maxLoad(config._maxLoad), _building(building) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

double Elevator::getOccupation() const
{
  if (_maxLoad == 0) return 0.0;

  int total_passengers = 0;
  for (auto const& client : _passengers)
  {
    total_passengers += client->_partySize;
  }
  return total_passengers / _maxLoad;
}

void Elevator::addPassenger(Floor* floor, Client* client)
{
  _passengers[floor].insert(client);
}

std::shared_ptr<std::set<Floor&>> Elevator::getDestinations() const
{
  std::shared_ptr<std::set<Floor&>> floors;

  for (auto const& client : _passengers) {
    floors->insert(client->_destination);
  }

  return floors;
}

std::shared_ptr<std::set<Client>> Elevator::getClients() const
{
}
