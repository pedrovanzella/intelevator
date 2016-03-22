//
// Created by Pedro Vanzella on 3/21/16.
//

#include "NearestNeighbourDispatcher.h"
#include "Elevator.h"
#include <memory>

std::shared_ptr<const Elevator> NearestNeighbourDispatcher::pick_next_elevator(const std::shared_ptr<const ClientArrival> ca) const
{
    auto elevators = _building->getElevators();
    auto floor = ca->getFloor();

    auto closest = elevators.front();

    for (auto elevator : elevators) {
        // get the current floor for the elevator
    }

    return closest;
}
