#include "Floor.h"
#include "Client.h"
#include "Direction.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "EventQueue.h"
#include "Scenario.h"
#include "Simulator.h"
#include <sstream>
#include <string>
#include <vector>

Floor::Floor(const int number, const float lambda)
    : _number(number), _lambda(lambda) {}

Floor::~Floor() {}

int Floor::getNumber() const { return _number; }

int Floor::getLambda() const { return _lambda; }

int Floor::clientsOnUpLine() const { return _upLine.size(); }

int Floor::clientsOnDownLine() const { return _downLine.size(); }

const std::vector<std::shared_ptr<Client>> Floor::getUpLine() const
{
  decltype(_upLine) upLine(_upLine);
  std::vector<std::shared_ptr<Client>> line;
  while (!upLine.empty()) {
    line.push_back(upLine.front());
    upLine.pop();
  }
  return line;
}

const std::vector<std::shared_ptr<Client>> Floor::getDownLine() const
{
  decltype(_downLine) downLine(_downLine);
  std::vector<std::shared_ptr<Client>> line;
  while (!downLine.empty()) {
    line.push_back(downLine.front());
    downLine.pop();
  }
  return line;
}

Direction Floor::compareTo(const Floor &other) const {
  if (other.getNumber() < _number)
    return Direction::Down;

  return Direction::Up;
}

void Floor::setEventFactory(const std::shared_ptr<EventFactory> eventFactory) {
  _eventFactory = eventFactory;
}

Direction Floor::addClient(const std::shared_ptr<Client> client) {
  int destination = client->getDestination();

  if (destination > _number) {
    _upLine.push(client);
    // LOG(INFO) << "Floor #" << _number << " received a client (size "
    //           << client->getPartySize() << ")"
    //           << " to go UP to floor #" << client->getDestination() << ".";
    return Direction::Up;
  } else if (destination < _number) {
    _downLine.push(client);
    // LOG(INFO) << "Floor #" << _number << " received a client (size "
    //           << client->getPartySize() << ")"
    //           << " to go DOWN to floor #" << client->getDestination() << ".";
    return Direction::Down;
  } else {
    std::ostringstream stream;
    stream << "Floor " << _number << " received a Client which destination is "
           << "this own floor! This should never "
           << "happen!";
    throw(stream.str());
  }
}

std::pair<std::set<int>, std::shared_ptr<Client>> Floor::boardElevator(const unsigned long time, std::shared_ptr<Elevator> elevator) {
  std::set<int> newStops;

  std::queue<std::shared_ptr<Client>>* lineToBoard = nullptr;

  if (elevator->getDestination().second == Direction::Up) {
    lineToBoard = &_upLine;
  } else if (elevator->getDestination().second == Direction::Down) {
    lineToBoard = &_downLine;
  } else {
    if (_upLine.size() > _downLine.size())
      lineToBoard = &_upLine;
    else
      lineToBoard = &_downLine;
  }

  while (lineToBoard->size() > 0 && elevator->canEnter(lineToBoard->front())) {
    auto client = lineToBoard->front();
    client->setPickupTime(time);
    elevator->addPassenger(client);
    newStops.insert(client->getDestination());
    lineToBoard->pop();

    LOG(INFO) << "Client #" << client->getId()
              << " boarded elevator #" << elevator->getNumber()
              << " (t=" << time << ").";
  }

  if (lineToBoard->empty())
    return { newStops, nullptr };

  return { newStops, lineToBoard->front() };
}

void Floor::createFutureArrival(const std::shared_ptr<EventQueue> eventQueue) {
  _eventFactory->createFutureArrival(eventQueue);
}

std::shared_ptr<std::vector<std::shared_ptr<Floor>>> Floor::create(const std::shared_ptr<const Simulator> simulator) {
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors(new std::vector<std::shared_ptr<Floor>>);

  auto scenario = simulator->getScenario();
  auto clock = simulator->getClock();
  auto random_engine = simulator->getRandomEngine();

  int i = 0;
  for (auto it : scenario->getFloors()) {
    auto f = std::make_shared<Floor>(i++, it);
    auto ef = std::make_shared<EventFactory>(clock, f, scenario, random_engine);
    f->setEventFactory(ef);
    floors->push_back(f);
  }

  return floors;
}

std::string Floor::str() const {
  std::ostringstream stream;
  stream << "Floor #" << _number << " :: UP[" << _upLine.size() << "], DOWN[" << _downLine.size() << "]";
  return stream.str();
}