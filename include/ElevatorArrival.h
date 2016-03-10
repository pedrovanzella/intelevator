#pragma once

#include "Elevator.h"
#include "Event.h"
#include "Floor.h"

class ElevatorArrival : public Event
{
public:
  ElevatorArrival(const float, const Elevator&, const Floor&);
  const Elevator& getElevator();
  const Floor& getFloor();

private:
  const Elevator& elevator;
  const Floor& floor;
};
