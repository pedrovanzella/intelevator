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
