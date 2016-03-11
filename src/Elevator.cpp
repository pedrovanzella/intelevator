#include "Elevator.h"

Elevator::Elevator(const Config& config)
 : maxLoad(config.maxLoad) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection()
{
  return Direction::idle;
}

int Elevator::getOccupation()
{
  return maxLoad; // TO-DO
}
