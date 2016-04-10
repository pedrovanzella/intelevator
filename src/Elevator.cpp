#include "Elevator.h"
#include <algorithm>
#include <memory>

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number),
    _capacity(capacity),
    _location(floor),
    _destination(floor),
    _status(Status::Stopped),
    _direction(Direction::Up),
    _stopAtNextLocation(false),
    _passengers(new std::vector<std::shared_ptr<const Client>>) {}

Elevator::~Elevator() {}

int Elevator::getNumber() const { return _number; }

int Elevator::getCapacity() const { return _capacity; }

int Elevator::getLocation() const { return _location; }

int Elevator::getDestination() const { return _destination; }

Status Elevator::getStatus() const { return _status; }

Direction Elevator::getDirection() const { return _direction; }

const std::shared_ptr<const std::vector<std::shared_ptr<const Client>>> Elevator::getPassengers() const {
  return _passengers;
}

int Elevator::getAvailableCapacity() const {
  if (_capacity == 0) return 0.0;

  int total_passengers = 0;
  for (auto client : *_passengers) total_passengers += client->getPartySize();
  return _capacity - total_passengers;
}

int Elevator::getNextLocation() const {
  if (_status == Status::Stopped)
    return _location;

  if (_status == Status::Moving)
  {
    if (_direction == Direction::Up)
      return _location + 1;

    if (_direction == Direction::Down)
      return _location - 1;
  }

  return _location;
}

void Elevator::setLocation(int location) { _location = location; }

void Elevator::setDestination(int destination) { _destination = destination; }

void Elevator::setDirection(Direction direction) { _direction = direction; }

void Elevator::setStatus(Status status) { _status = status; }

std::shared_ptr<std::vector<std::shared_ptr<const Client>>> Elevator::dropPassengersToCurrentLocation() {
  /* Copy every client bound to current _location into passengersToDrop container. */
  decltype(_passengers) passengersToDrop(new std::vector<std::shared_ptr<const Client>>);
  std::copy_if(_passengers->begin(),
               _passengers->end(),
               std::back_inserter(*passengersToDrop),
               [&](std::shared_ptr<const Client> c) {
                 return (c->getDestination() == _location);
               });

  /* Creates a new container with the difference between all the clients inside
    the elevator and the passengers about to drop off the elevator. */
  decltype(_passengers) remainingPassengers(new std::vector<std::shared_ptr<const Client>>);
  std::set_difference(_passengers->begin(),
                      _passengers->end(),
                      passengersToDrop->begin(),
                      passengersToDrop->end(),
                      std::inserter(*remainingPassengers, remainingPassengers->begin()));

  /* Swaps the Clients container with the Difference container. */
  _passengers.swap(remainingPassengers);

  /* Returns the passengers about to drop off the elevador. */
  return passengersToDrop;
}

void Elevator::stopAtNextLocation() { _stopAtNextLocation = true; }

void Elevator::addPassenger(std::shared_ptr<const Client> client) {
  _passengers->push_back(client);
}

void Elevator::start() { _status = Status::Moving; }

void Elevator::stop() { _status = Status::Stopped; }

void Elevator::turn() {
  if (_direction == Direction::Up)
    _direction = Direction::Down;
  else
    _direction = Direction::Up;
}

void Elevator::update() {
  switch (_status) {
    case Status::Moving: {
      if (_direction == Direction::Up) {
        _location++;
      } else if (_direction == Direction::Down) {
        _location--;
      }

      if (_stopAtNextLocation) {
        stop();
        _stopAtNextLocation = false;
      }

      if (_location == _destination) {
        stop();
        setDirection(Direction::None);
      }
    } break;
    case Status::Stopped: {
      // Passos:
      //  1 - se houver alguém que queira descer aqui, desembarcá-los;
      decltype(_passengers) this_floor_passengers;

      std::copy_if(_passengers->begin(), _passengers->end(), std::back_inserter(*this_floor_passengers),
      [&](std::shared_ptr<const Client> client) {
        return client->getDestination() == _location;
      });
      //  2 - se não tem mais nenhum passageiro e não tem mais pra onde ir, o
      //  elevador não tem mais nada pra fazer e deve ficar em IDLE
      //  3 - se tem pra onde ir, o elevador deve se mover pra lá
    } break;
    default:
      break;
  }
}