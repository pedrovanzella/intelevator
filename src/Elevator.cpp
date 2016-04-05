#include <memory>
#include "Elevator.h"

Elevator::Elevator(int number, int capacity, std::shared_ptr<const Floor> floor)
  : _number(number)
  , _capacity(capacity)
  , _current_floor(floor) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

double Elevator::getOccupation() const
{
  if (_capacity == 0) return 0.0;

  int total_passengers = 0;
  for (auto const& client : _passengers)
  {
    total_passengers += client->getPartySize();
  }
  return total_passengers / _capacity;
}

int Elevator::getNumber() const
{
  return _number;
}

int Elevator::getCapacity() const
{
  return _capacity;
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

void Elevator::notify(const std::shared_ptr<const Event> event) const
{
  if (event->getType() == EventType::cycleElevators)
  {
    LOG(INFO) << "Elevator(" << getNumber() << ") :: " << Helpers::eventTypeName(event->getType());
  }
}