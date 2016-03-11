#include "ElevatorArrival.h"
#include "EventType.h"

ElevatorArrival::ElevatorArrival(const float eventTime, const Elevator& elevator, const Floor& floor)
 : Event(eventTime, EventType::elevatorArrival)
 , elevator(elevator)
 , floor(floor) {}

const Elevator& ElevatorArrival::getElevator() const
{
  return this->elevator;
}

const Floor& ElevatorArrival::getFloor() const
{
  return this->floor;
}
