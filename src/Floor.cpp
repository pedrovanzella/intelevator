#include "Floor.h"

Floor::Floor(int number)
 : number(number) {}

int Floor::getNumber()
{
  return this->number;
}

void Floor::notify(const Event& event)
{
  // Handle events
}