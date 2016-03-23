#include "Event.h"
#include "Floor.h"

Floor::Floor(int number)
  : _number(number) {}

Floor::~Floor() {}

int Floor::getNumber() const
{
  return _number;
}

void Floor::notify(const std::shared_ptr<const Event> event) const
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
