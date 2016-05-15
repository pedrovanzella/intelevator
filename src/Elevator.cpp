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
    _destination(floor),
    _direction(Direction::None),
    _passengers(new std::vector<std::shared_ptr<Client>>) {}

Elevator::~Elevator() {}

int Elevator::getNumber() const { return _number; }

int Elevator::getCapacity() const { return _capacity; }

int Elevator::getLocation() const { return _location; }

int Elevator::getDestination() const { return _destination; }

Direction Elevator::getDirection() const {
  return Direction::Up;
}

const std::shared_ptr<const std::vector<std::shared_ptr<Client>>> Elevator::getPassengers() const {
  return _passengers;
}

int Elevator::getAvailableCapacity() const {
  if (_capacity == 0) return 0.0;

  int total_passengers = 0;
  for (auto client : *_passengers) total_passengers += client->getPartySize();
  return _capacity - total_passengers;
}

bool Elevator::canEnter(std::shared_ptr<const Client> client) const {
  return getAvailableCapacity() >= client->getPartySize();
}

void Elevator::setDestination(int destination) {

  _destination = destination;
  LOG_IF(INFO, _destination != -1) << "Elevator #" << _number << " received new destination: floor #" << _destination << ".";

  if (destination == -1) {
    _direction = Direction::None;
  }
  else {
    if (_destination > _location)
      _direction = Direction::Up;
    else if (_destination < _location)
      _direction = Direction::Down;
    else
      _direction = Direction::None;
  }
 }

std::shared_ptr<std::vector<std::shared_ptr<Client>>> Elevator::dropPassengersToCurrentLocation() {
  /* Copy every client bound to current _location into passengersToDrop container. */
  decltype(_passengers) passengersToDrop(new std::vector<std::shared_ptr<Client>>);
  std::copy_if(_passengers->begin(),
               _passengers->end(),
               std::back_inserter(*passengersToDrop),
               [&](std::shared_ptr<Client> c) {
                 return (c->getDestination() == _location);
               });

  /* Creates a new container with the difference between all the clients inside
    the elevator and the passengers about to drop off the elevator. */
  decltype(_passengers) remainingPassengers(new std::vector<std::shared_ptr<Client>>);
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

void Elevator::addPassenger(std::shared_ptr<Client> client) {
  _passengers->push_back(client);
  LOG(INFO) << "Client #" << client->getId()
            << " boarded elevator #" << getNumber() << ".";
}

void Elevator::move() {
    if (_direction == Direction::Up) {
      _location++;
      // LOG(INFO) << "Elevator #" << _number
      //   << " went UP to floor #" << _location << ".";
    } else if (_direction == Direction::Down) {
      _location--;
      // LOG(INFO) << "Elevator #" << _number
      //   << " went DOWN to floor #" << _location << ".";
    } else {
      // LOG(INFO) << "Elevator #" << _number
      //   << " stayed at floor #" << _location << ".";
    }
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