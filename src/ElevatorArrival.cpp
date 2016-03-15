#include "ElevatorArrival.h"
#include "EventType.h"

ElevatorArrival::ElevatorArrival(const float eventTime, const Elevator& elevator, const Floor& floor)
 : Event(eventTime, EventType::elevatorArrival)
 , _elevator(elevator)
 , _floor(floor) {}

const Elevator& ElevatorArrival::getElevator() const
{
  return _elevator;
}

const Floor& ElevatorArrival::getFloor() const
{
  return _floor;
}
