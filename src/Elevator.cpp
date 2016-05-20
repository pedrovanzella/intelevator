#include "Elevator.h"
#include "Client.h"
#include "Direction.h"
#include "Event.h"
#include "Scenario.h"
#include "Simulator.h"
#include <algorithm>
#include <glog/logging.h>
#include <memory>

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number),
    _capacity(capacity),
    _location(floor),
    _destination(-1),
    _passengers(new std::vector<std::shared_ptr<Client>>) {}

Elevator::~Elevator() {}

int Elevator::getNumber() const { return _number; }

int Elevator::getCapacity() const { return _capacity; }

int Elevator::getLocation() const { return _location; }

int Elevator::getDestination() const { return _destination; }

const std::shared_ptr<const std::vector<std::shared_ptr<Client>>> Elevator::getPassengers() const { return _passengers; }

bool Elevator::canEnter(std::shared_ptr<const Client> client) const {
  int total_passengers = 0;
  for (auto client : *_passengers) total_passengers += client->getPartySize();
  return (_capacity - total_passengers) >= client->getPartySize();
}

Direction Elevator::getDirection() const {
  if (_destination == -1 || _destination == _location) return Direction::None;
  if (_destination > _location) return Direction::Up;
  return Direction::Down;
}

void Elevator::setDestination(int destination) { _destination = destination; }

void Elevator::addPassenger(std::shared_ptr<Client> client) {
  _passengers->push_back(client);
}

Direction Elevator::move() {
  auto direction = getDirection();
  switch (direction) {
  case Direction::Up:
    _location++;
    break;
  case Direction::Down:
    _location--;
    break;
  default:
    break;
  }

  return direction;
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
  for (int i = 0; i < scenario->getElevators(); i++) {
    auto e = std::make_shared<Elevator>(i, scenario->getCapacity(), 0);
    elevators->push_back(e);
  }

  return elevators;
}
