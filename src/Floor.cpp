#include "ClientArrival.h"
#include "Event.h"
#include "Floor.h"
#include <sstream>
#include <string>

Floor::Floor(int number, int population)
  : _number(number)
  , _population(population) {}

Floor::~Floor() {}

int Floor::getNumber() const
{
  return _number;
}

int Floor::getPopulation() const
{
  return _population;
}

bool Floor::hasUpCall() const
{
  return _upLine.size() > 0;
}

bool Floor::hasDownCall() const
{
  return _downLine.size() > 0;
}

Direction Floor::compareTo(const Floor &other) const
{
    if (other.getNumber() < _number)
      return Direction::Down;

    return Direction::Up;
}

void Floor::addClient(const std::shared_ptr<const Client> client)
{
  int destination = client->getDestination();

  if (destination > _number) {
    _upLine.push(client);
    LOG(INFO) << "Floor #" << _number << " received a client to go UP to floor #" << client->getDestination() << ".";
  }
  else if (destination < _number) {
    _downLine.push(client);
   LOG(INFO) << "Floor #" << _number << " received a client to go DOWN to floor #" << client->getDestination() << ".";
  }
  else
  {
    std::ostringstream stream;
    stream << "Floor " << _number << " received a Client which destination is this own floor! This should never happen!";
    throw(stream.str());
  }
}