//
// Created by Pedro Vanzella on 3/23/16.
//

#include "BetterNearestNeighbourDispatcher.h"
#include "Elevator.h"
#include <memory>
#include <algorithm>
#include "Direction.h"
#include "NearestNeighbourDispatcher.h"

std::shared_ptr<const Elevator> BetterNearestNeighbourDispatcher::pick_next_elevator(const std::shared_ptr<const ClientArrival> ca) const
{
    auto elevators = _building->getElevators();
    auto request_floor = ca->getFloor();

    auto closest = elevators.front();

    decltype(elevators) sd_elevators;

    // Find all elevators that are going that way, or are idle
    std::copy_if(elevators.begin(), elevators.end(), std::back_inserter(sd_elevators),
    [&](std::shared_ptr<const Elevator> el) {
        return (el->getDirection() == el->getCurrentFloor()->compareTo(*request_floor)) ||
               (el->getDirection() == Direction::idle);
    });

    // if no elevators are idle or going that way, then look through all elevators
    if (sd_elevators.size() == 0) {
        NearestNeighbourDispatcher disp(_building);

        return disp.pick_next_elevator(ca);
    }

    for (auto elevator : sd_elevators) {
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
