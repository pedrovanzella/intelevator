#include "Event.h"
#include "Floor.h"

Floor::Floor(int number)
  : number(number) {}

Floor::~Floor() {}

int Floor::getNumber() const
{
  return this->number;
}

void Floor::notify(const Event& event) const
{
  // Handle events
}
