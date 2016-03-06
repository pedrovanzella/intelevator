#include "Elevator.h"

Elevator::Elevator() {}

Direction Elevator::direction()
{
  return Direction::idle;
}

int Elevator::occupation()
{
  return 0;
}
