#include "Elevator.h"
#include "Simulator.h"
#include <algorithm>
#include <memory>
#include <glog/logging.h>
#include "Trip.h"

Elevator::Elevator(int number, int capacity, int floor)
  : _number(number),
    _capacity(capacity),
    _location(floor),
    _destination(floor),
    _status(Status::Idle),
    _direction(Direction::None),
    _stopAtNextLocation(false),
    _passengers(new std::vector<std::shared_ptr<Client>>) {}

Elevator::~Elevator() {}

int Elevator::getNumber() const { return _number; }

int Elevator::getCapacity() const { return _capacity; }

int Elevator::getLocation() const { return _location; }

int Elevator::getDestination() const { return _destination; }

Status Elevator::getStatus() const { return _status; }

Direction Elevator::getDirection() const { return _direction; }

const std::shared_ptr<const std::vector<std::shared_ptr<Client>>> Elevator::getPassengers() const {
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

bool Elevator::canEnter(std::shared_ptr<const Client> client) const {
  return getAvailableCapacity() >= client->getPartySize();
}

void Elevator::setLocation(int location) { _location = location; }

void Elevator::setDestination(int destination) {
  LOG(INFO) << "Elevator #" << _number << " received new destination: floor #" << destination << ".";

  _destination = destination;

  refreshDirection();

  start();
 }

void Elevator::setDirection(Direction direction) { _direction = direction; }

void Elevator::setStatus(Status status) { _status = status; }

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

void Elevator::mustStopAtNextLocation() { _stopAtNextLocation = true; }

void Elevator::addPassenger(std::shared_ptr<Client> client) {
  _passengers->push_back(client);
  LOG(INFO) << "Client with size " << client->getPartySize() << " boarded elevator #" << getNumber() << ".";
}

void Elevator::start() { _status = Status::Moving; }

void Elevator::stop() { _status = Status::Stopped; refreshDirection(); }

void Elevator::idle() { _status = Status::Idle; }

void Elevator::turn() {
  if (_direction == Direction::Up)
    _direction = Direction::Down;
  else
    _direction = Direction::Up;
}

void Elevator::goToNextLocation() {
  switch (_status) {
    case Status::Moving: {
      if (_direction == Direction::Up) {
        _location++;
        // LOG(INFO) << "Elevator #" << getNumber()
        //   << " went UP to floor #" << getLocation() << ".";

      } else if (_direction == Direction::Down) {
        _location--;
        // LOG(INFO) << "Elevator #" << getNumber()
        //   << " went DOWN to floor #" << getLocation() << ".";
      } else {
        // LOG(INFO) << "Elevator #" << getNumber()
        //   << " stayed at floor #" << getLocation() << ".";
      }

      if (_stopAtNextLocation) {
        stop();
        _stopAtNextLocation = false;
      }

      if (_location == _destination) {
        idle();
      }
    } break;
    default:
      break;
  }
}

std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Elevator::create(const std::shared_ptr<Simulator> simulator) {
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators(new std::vector<std::shared_ptr<Elevator>>);

  auto scenario = simulator->getScenario();
  for (int i = 0; i < scenario->getElevators(); i++) {
    auto e = std::make_shared<Elevator>(i, scenario->getCapacity(), 0);
    elevators->push_back(e);
  }

  return elevators;
}

void Elevator::refreshDirection() {
  if (_destination > _location)
    setDirection(Direction::Up);
  else if (_destination < _location)
    setDirection(Direction::Down);
  else
    setDirection(Direction::None);
}