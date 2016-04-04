#include <memory>
#include "Elevator.h"
#include "NearestNeighbourDispatcher.h"

std::shared_ptr<const Elevator> NearestNeighbourDispatcher::pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                                                                 const std::shared_ptr<const Building> building,
                                                                 const std::shared_ptr<const ClientArrival> ca) const
{
  auto elevators = building->getElevators();
  auto request_floor = ca->getFloor();

  auto closest = elevators->front();

  for (auto elevator : *elevators)
  {
    auto where_it_is = elevator->getCurrentFloor()->getNumber();
    auto where_to = request_floor->getNumber();
    auto where_the_closest_is = closest->getCurrentFloor()->getNumber();

    auto distance = where_it_is - where_to;
    auto closest_distance = where_the_closest_is - where_to;

    if (distance < closest_distance) {
      closest = elevator;
    }
  }

  return closest;
}
