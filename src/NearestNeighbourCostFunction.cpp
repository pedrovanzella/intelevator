#include "NearestNeighbourCostFunction.h"
#include "Building.h"
#include "Elevator.h"
#include "Client.h"

float NearestNeighbourCostFunction::calculate(
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> c) const {
  return abs(c->getArrivalFloor() - elevator->getLocation());
}
