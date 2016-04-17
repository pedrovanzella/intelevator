#include "ClientArrival.h"
#include "Direction.h"
#include "Event.h"
#include "Floor.h"
#include <set>
#include <sstream>
#include <string>

Floor::Floor(int number, int population)
  : _number(number)
  , _population(population)
  , _eventFactory(new EventFactory) {}

Floor::~Floor() {}

int Floor::getNumber() const
{
  return _number;
}

int Floor::getPopulation() const
{
  return _population;
}

Direction Floor::compareTo(const Floor &other) const
{
    if (other.getNumber() < _number)
      return Direction::Down;

    return Direction::Up;
}

void Floor::addClient(const std::shared_ptr<Client> client)
{
  int destination = client->getDestination();

  if (destination > _number) {
    _upLine.push(client);
    LOG(INFO) << "Floor #" << _number << " received a client (size " << client->getPartySize() << ") to go UP to floor #" << client->getDestination() << ".";
  }
  else if (destination < _number) {
    _downLine.push(client);
   LOG(INFO) << "Floor #" << _number << " received a client (size " << client->getPartySize() << ") to go DOWN to floor #" << client->getDestination() << ".";
  }
  else
  {
    std::ostringstream stream;
    stream << "Floor " << _number << " received a Client which destination is this own floor! This should never happen!";
    throw(stream.str());
  }
}

std::set<int> Floor::boardElevator(std::shared_ptr<Elevator> elevator)
{
  std::set<int> newStops;

  if (elevator->getDirection() != Direction::Down) {
    while (_upLine.size() > 0 && elevator->canEnter(_upLine.front())) {
      auto client = _upLine.front();
      elevator->addPassenger(client);
      newStops.insert(client->getDestination());
      _upLine.pop();
    }
  }
  else if (elevator->getDirection() == Direction::Down) {
    while (_downLine.size() > 0 && elevator->canEnter(_downLine.front())) {
      auto client = _downLine.front();
      elevator->addPassenger(client);
      newStops.insert(client->getDestination());
      _downLine.pop();
    }
  }

  return newStops;
}