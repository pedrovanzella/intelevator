#include "NearestNeighbourCostFunction.h"
#include "Building.h"
#include "Client.h"
#include "Elevator.h"

float NearestNeighbourCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) const {
  return abs(client->getArrivalFloor() - elevator->getLocation());
}
