#include "WeightedCostFunction.h"
#include "Client.h"
#include "Elevator.h"
#include <cmath>
#include <cstdlib>

float WeightedCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) {
  if (elevator->getOccupation() == 0.0)
    return std::abs(client->getArrivalFloor() - elevator->getLocation());

  return std::abs(client->getArrivalFloor() - elevator->getLocation()) / std::sqrt(elevator->getOccupation());
}
