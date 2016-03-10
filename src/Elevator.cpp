#include "Elevator.h"

Elevator::Elevator(const Building& building, Floor& location)
 : building(building)
 , location(location) {}

Elevator::~Elevator() {}

const Building& Elevator::getBuilding()
{
  return this->building;
}

Floor& Elevator::getLocation()
{
  return this->location;
}

Direction Elevator::getDirection()
{
  return Direction::idle;
}

int Elevator::getOccupation()
{
  return 0;
}
