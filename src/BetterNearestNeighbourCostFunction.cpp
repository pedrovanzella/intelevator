#include "BetterNearestNeighbourCostFunction.h"
#include "NearestNeighbourCostFunction.h"
#include "Building.h"
#include "Client.h"
#include "Elevator.h"
#include "Floor.h"
#include "Status.h"
#include <algorithm>
#include <cmath>

float BetterNearestNeighbourCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) {

  auto where_it_is = elevator->getLocation();
  auto where_to = client->getArrivalFloor();
  auto distance = where_it_is - where_to;

  auto floors = building->getFloors();
  auto current_floor = floors->at(where_it_is);
  auto request_floor = floors->at(where_to);

  if (elevator->getStatus() == Status::Idle)
    return abs(distance) / std::sqrt(4.0);

  if (elevator->getDirection() == current_floor->compareTo(*request_floor))
    return abs(distance) / std::sqrt(2.0);

  return abs(distance);
}
