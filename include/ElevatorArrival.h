#pragma once

#include <memory>
#include "Elevator.h"
#include "Event.h"
#include "Floor.h"



class ElevatorArrival : public Event
{
public:
  ElevatorArrival(const float, const std::shared_ptr<const Elevator> elevator, const std::shared_ptr<const Floor> floor);
  const std::shared_ptr<const Elevator> getElevator() const;
  const std::shared_ptr<const Floor> getFloor() const;

private:
  const std::shared_ptr<const Elevator> _elevator;
  const std::shared_ptr<const Floor> _floor;
};
