#include "Event.h"
#include "Floor.h"

Floor::Floor(int number) {}

Floor::~Floor() {}

int Floor::getNumber()
{
  return this->number;
}

void Floor::notify(const Event& event)
{
  // Handle events
}