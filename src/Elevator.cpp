#include "Elevator.h"

Elevator::Elevator(const Config& config, const Building* building)
  : _maxLoad(config._maxLoad), _building(building) {}

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
