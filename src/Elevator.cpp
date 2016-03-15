#include "Elevator.h"

Elevator::Elevator(const Config& config)
 : _maxLoad(config.maxLoad) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

int Elevator::getOccupation() const
{
  return 0; // TO-DO
}
