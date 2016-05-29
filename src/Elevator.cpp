#include "Elevator.h"
#include "Client.h"
#include "Direction.h"
#include "Event.h"
#include "Scenario.h"
#include "Simulator.h"
#include "Status.h"
#include <algorithm>
#include <glog/logging.h>
#include <memory>

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number),
    _capacity(capacity),
    _location(floor),
    _destination({ floor, Direction::Up }),
    _status(Status::Idle),
    _direction(Direction::Up),
    _passengers(new std::vector<std::shared_ptr<Client>>) {}

Elevator::~Elevator() {}

int Elevator::getNumber() const { return _number; }

int Elevator::getCapacity() const { return _capacity; }

int Elevator::getLocation() const { return _location; }

std::pair<int, Direction> Elevator::getDestination() const { return _destination; }

Status Elevator::getStatus() const { return _status; }

Direction Elevator::getDirection() const { return _direction; }

const std::shared_ptr<const std::vector<std::shared_ptr<Client>>> Elevator::getPassengers() const { return _passengers; }

float Elevator::getOccupation() const
{
  int totalweight = 0;
  for (auto p : *_passengers) {
    totalweight += p->getPartySize();
  }

  if (totalweight == 0) {
    return 0.0;
  }

  return _capacity / totalweight;
}

void Elevator::setDestination(std::pair<int, Direction> destination) {
  _destination = destination;

  if (_destination.first > _location) {
    _status = Status::Moving;
    _direction = Direction::Up;
  } else if (_destination.first < _location) {
    _status = Status::Moving;
    _direction = Direction::Down;
  } else {
    _status = Status::Idle;
  }
}

bool Elevator::canEnter(std::shared_ptr<const Client> client) const {
  int total_passengers = 0;
  for (auto client : *_passengers) total_passengers += client->getPartySize();
  return (_capacity - total_passengers) >= client->getPartySize();
}

void Elevator::addPassenger(std::shared_ptr<Client> client) {
  _passengers->push_back(client);
}

void Elevator::move() {
  if (_status == Status::Idle || _status == Status::Stopped) return;

  switch (_direction) {
  case Direction::Up:
    _location++;
    break;
  case Direction::Down:
    _location--;
    break;
  }

  if (_location == _destination.first)
    _status = Status::Idle;
}

std::shared_ptr<std::vector<std::shared_ptr<Client>>> Elevator::dropPassengersToCurrentLocation() {
  decltype(_passengers) passengersToDrop(new std::vector<std::shared_ptr<Client>>);

  for (auto iter = _passengers->begin(); iter != _passengers->end();) {
    auto passenger = *iter;
    if (passenger->getDestination() == _location) {
      passengersToDrop->push_back(passenger);
      iter = _passengers->erase(iter);
    } else {
      ++iter;
    }
  }
  return passengersToDrop;
}

std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Elevator::create(const std::shared_ptr<const Simulator> simulator) {
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators(new std::vector<std::shared_ptr<Elevator>>);

  auto scenario = simulator->getScenario();
  for (int i = 0; i < scenario->getElevatorCount(); i++) {
    auto e = std::make_shared<Elevator>(i, scenario->getCapacity(), 0);
    elevators->push_back(e);
  }

  return elevators;
}
