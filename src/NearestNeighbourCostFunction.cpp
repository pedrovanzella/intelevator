#include "NearestNeighbourCostFunction.h"
#include "Building.h"
#include "Client.h"
#include "Elevator.h"
#include "Floor.h"
#include <cstdlib>

float NearestNeighbourCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) {

  auto where_it_is = elevator->getLocation();
  auto where_to = client->getArrivalFloor();
  auto distance = where_it_is - where_to;

  return std::abs(distance);
}
