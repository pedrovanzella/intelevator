#include <memory>
#include "Elevator.h"

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number)
  , _capacity(capacity)
  , _location(floor)
  , _destination(floor)
  {}

Elevator::~Elevator() {}

int Elevator::getNumber() const
{
  return _number;
}

int Elevator::getCapacity() const
{
  return _capacity;
}

int Elevator::getLocation() const
{
  return _location;
}

int Elevator::getDestination() const
{
  return _destination;
}

void Elevator::setDestination(int destination)
{
  _destination = destination;
}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

int Elevator::getAvailableCapacity() const
{
  if (_capacity == 0) return 0.0;

  int total_passengers = 0;
  for (auto const& client : _passengers)
  {
    total_passengers += client->getPartySize();
  }
  return _capacity - total_passengers;
}

void Elevator::addPassenger(std::shared_ptr<const Client> client)
{
  _passengers.insert(client);
}

void Elevator::notify(const std::shared_ptr<const Event> event) const
{
  if (event->getType() == EventType::cycleElevators)
  {
    LOG(INFO) << "Elevator(" << getNumber() << ") :: " << Helpers::eventTypeName(event->getType());
  }
}