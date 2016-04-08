#include <memory>
#include "Elevator.h"

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number)
  , _capacity(capacity)
  , _location(floor)
  , _destination(floor)
  , _status(Status::Stopped)
  , _direction(Direction::Up)
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

Status Elevator::getStatus() const
{
  return _status;
}

Direction Elevator::getDirection() const
{
  return _direction;
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

void Elevator::setLocation(int location)
{
  _location = location;
}

void Elevator::setDestination(int destination)
{
  _destination = destination;
}

void Elevator::addPassenger(std::shared_ptr<const Client> client)
{
  _passengers.insert(client);
}

void Elevator::notify(const std::shared_ptr<const Event> event)
{
  if (event->getType() == EventType::cycleElevators)
  {
    LOG(INFO) << "Elevator " << _number << " reacting to event " << event->str() << ".";
    move();
  }
}

void Elevator::start()
{
  _status = Status::Moving;
}

void Elevator::stop()
{
  _status = Status::Stopped;
}

void Elevator::turn()
{
  if (_direction == Direction::Up)
    _direction = Direction::Down;
  else
    _direction = Direction::Up;
}

void Elevator::move()
{
  if (_direction == Direction::Up)
  {
    _location += 1;

    if (_location == _destination)
    {
      // deve criar um evento de elevator arrival e enfileirar
    }
  }
  else
  {
    _location -= 1;

    if (_location == _destination)
    {
      // deve criar um evento de elevator arrival e enfileirar
    }
  }
}