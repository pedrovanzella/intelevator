#include "ElevatorArrival.h"
#include "EventType.h"

ElevatorArrival::ElevatorArrival(const unsigned long eventTime, int elevator, int location)
 : Event(eventTime, EventType::elevatorArrival)
 , _elevator(elevator)
 , _location(location) {}

int ElevatorArrival::getElevator() const
{
  return _elevator;
}

int ElevatorArrival::getLocation() const
{
  return _location;
}
