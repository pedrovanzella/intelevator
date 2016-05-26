#include "WeightedCostFunction.h"
#include "Elevator.h"
#include "Client.h"
#include <cmath>

float WeightedCostFunction::calculate(const std::shared_ptr<const Elevator> elevator, const std::shared_ptr<const Client> c) const
{
  if (elevator->getOccupation() == 0.0) {
    return abs(c->getArrivalFloor() - elevator->getLocation());
  }
  return abs(c->getArrivalFloor() - elevator->getLocation()) / std::sqrt(elevator->getCapacity());
}
