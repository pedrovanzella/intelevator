#include <memory>
#include "Elevator.h"

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number)
  , _capacity(capacity)
  , _location(floor)
  , _destination(floor)
  , _status(Status::Stopped)
  , _direction(Direction::Up)
  , _stopAtNextLocation(false)
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

int Elevator::getNextLocation() const
{
  if (_status == Status::Moving) {
    if (_direction == Direction::Up) {
      return _location + 1;
    } else if (_direction == Direction::Down) {
      return _location - 1;
    } else {
      return _location;
    }
  } else {
    return _location;
  }
}

void Elevator::setLocation(int location)
{
  _location = location;
}

void Elevator::setDestination(int destination)
{
  _destination = destination;
}

void Elevator::setDirection(Direction direction)
{
  _direction = direction;
}
void Elevator::setStatus(Status status)
{
  _status = status;
}

void Elevator::stopAtNextLocation()
{
  _stopAtNextLocation = true;
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
  switch (_status)
  {
    case Status::Moving:
    {
      if (_direction == Direction::Up)
      {
        _location++;
      } else if (_direction == Direction::Down)
      {
        _location--;
      }

      if (_stopAtNextLocation)
      {
        stop();
        _stopAtNextLocation = false;
      }

      // if (algum passageiro quer descer em _location) {
      //   stop();
      //   return;
      // }

      if (_location == _destination)
      {
        stop();
        setDirection(Direction::None);
      }
    }
    break;
    case Status::Stopped:
    {
      // Passos:
      //  1 - se houver alguém que queira descer aqui, desembarcá-los;
      //  2 - se não tem mais nenhum passageiro e não tem mais pra onde ir, o elevador não tem mais nada pra fazer e deve ficar em IDLE
      //  3 - se tem pra onde ir, o elevador deve se mover pra lá
    }
    break;
    default:
      break;
    }
  }