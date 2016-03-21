//
// Created by Pedro Vanzella on 3/21/16.
//

#include "NearestNeighbourDispatcher.h"
#include "Elevator.h"
#include <memory>

std::shared_ptr<Elevator> NearestNeighbourDispatcher::pick_next_elevator(const std::shared_ptr<const ClientArrival> ca)
{
    auto elevators = _building->getElevators();
    return nullptr;
}
