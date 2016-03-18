#include "ElevatorArrival.h"
#include "EventType.h"

ElevatorArrival::ElevatorArrival(const float eventTime, const std::shared_ptr<const Elevator> elevator, const std::shared_ptr<const Floor> floor)
 : Event(eventTime, EventType::elevatorArrival)
 , _elevator(elevator)
 , _floor(floor) {}

const std::shared_ptr<const Elevator> ElevatorArrival::getElevator() const
{
  return _elevator;
}

const std::shared_ptr<const Floor> ElevatorArrival::getFloor() const
{
  return _floor;
}
