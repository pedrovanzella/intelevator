#include "Event.h"
#include "Floor.h"

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

void Floor::notify(const std::shared_ptr<const Event> event)
{
  // Handle events
}

Direction Floor::compareTo(const Floor &other) const
{
    if (other.getNumber() < _number)
        return Direction::descending;
    if (other.getNumber() > _number)
        return Direction::ascending;

    return Direction::idle;
}
