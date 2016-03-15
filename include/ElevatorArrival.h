#pragma once

#include "Elevator.h"
#include "Event.h"
#include "Floor.h"

class ElevatorArrival : public Event
{
public:
  ElevatorArrival(const float, const Elevator&, const Floor&);
  const Elevator& getElevator() const;
  const Floor& getFloor() const;

private:
  const Elevator& _elevator;
  const Floor& _floor;
};
