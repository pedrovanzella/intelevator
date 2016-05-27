#include "WeightedCostFunction.h"
#include "Client.h"
#include "Elevator.h"
#include <cmath>

float WeightedCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) {
  if (elevator->getOccupation() == 0.0)
    return abs(client->getArrivalFloor() - elevator->getLocation());

  return abs(client->getArrivalFloor() - elevator->getLocation()) / std::sqrt(elevator->getOccupation());
}
