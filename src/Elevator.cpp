#include "Elevator.h"

Elevator::Elevator(const Config& config)
 : _maxLoad(config._maxLoad) {}

Elevator::~Elevator() {}

Direction Elevator::getDirection() const
{
  return Direction::idle;
}

double Elevator::getOccupation() const
{
  if (_maxLoad == 0) return 0.0;

  int total_passengers = 0;
  for (auto const& floors : _passengers)
  {
    for (auto const& clients : floors.second)
    {
      total_passengers += clients->_partySize;
    }
  }
  return total_passengers / _maxLoad;
}
