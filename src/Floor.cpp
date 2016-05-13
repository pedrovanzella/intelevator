#include "Floor.h"
#include "Simulator.h"
#include <sstream>
#include <string>

Floor::Floor(const int number, const int population, const float lambda)
    : _number(number), _population(population), _lambda(lambda) {}

Floor::~Floor() {}

int Floor::getNumber() const { return _number; }

int Floor::getLambda() const { return _lambda; }

int Floor::getPopulation() const { return _population; }

int Floor::clientsOnUpLine() const { return _upLine.size(); }

int Floor::clientsOnDownLine() const { return _downLine.size(); }

Direction Floor::compareTo(const Floor &other) const {
  if (other.getNumber() < _number)
    return Direction::Down;

  if (other.getNumber() > _number)
    return Direction::Up;

  return Direction::None;
}

void Floor::setEventFactory(const std::shared_ptr<EventFactory> eventFactory) {
  _eventFactory = eventFactory;
}

void Floor::addClient(const std::shared_ptr<Client> client) {
  int destination = client->getDestination();

  if (destination > _number) {
    _upLine.push(client);
    // LOG(INFO) << "Floor #" << _number << " received a client (size "
    //           << client->getPartySize() << ")"
    //           << " to go UP to floor #" << client->getDestination() << ".";
  } else if (destination < _number) {
    _downLine.push(client);
    // LOG(INFO) << "Floor #" << _number << " received a client (size "
    //           << client->getPartySize() << ")"
    //           << " to go DOWN to floor #" << client->getDestination() << ".";
  } else {
    std::ostringstream stream;
    stream << "Floor " << _number << " received a Client which destination is "
           << "this own floor! This should never "
           << "happen!";
    throw(stream.str());
  }
}

std::set<int> Floor::boardElevator(std::shared_ptr<Elevator> elevator) {
  std::set<int> newStops;

  if (elevator->getDirection() != Direction::Down) {
    while (_upLine.size() > 0 && elevator->canEnter(_upLine.front())) {
      auto client = _upLine.front();
      elevator->addPassenger(client);
      newStops.insert(client->getDestination());
      _upLine.pop();
    }
  } else if (elevator->getDirection() == Direction::Down) {
    while (_downLine.size() > 0 && elevator->canEnter(_downLine.front())) {
      auto client = _downLine.front();
      elevator->addPassenger(client);
      newStops.insert(client->getDestination());
      _downLine.pop();
    }
  }

  return newStops;
}

void Floor::createFutureArrival(const std::shared_ptr<EventQueue> eventQueue) {
  _eventFactory->createFutureArrival(eventQueue);
}

std::shared_ptr<std::vector<std::shared_ptr<Floor>>> Floor::create(const std::shared_ptr<Simulator> simulator) {
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors(new std::vector<std::shared_ptr<Floor>>);

  auto scenario = simulator->getScenario();
  auto clock = simulator->getClock();

  int i = 0;
  for (auto it : scenario->getFloors()) {
    auto f = std::make_shared<Floor>(i++, it.first, it.second);
    auto ef = std::make_shared<EventFactory>(clock, f, scenario);
    f->setEventFactory(ef);
    floors->push_back(f);
  }

  return floors;
}