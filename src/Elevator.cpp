#include "Elevator.h"

Elevator::Elevator(const Config& config)
 : maxLoad(config.maxLoad) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

int Elevator::getOccupation() const
{
  return maxLoad; // TO-DO
}
