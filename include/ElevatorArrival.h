#pragma once

#include <memory>
#include "Elevator.h"
#include "Event.h"
#include "Floor.h"

class ElevatorArrival : public Event
{
public:
  ElevatorArrival(const unsigned long eventTime, int elevator, int location);
  int getElevator() const;
  int getLocation() const;

private:
  int _elevator;
  int _location;
};
