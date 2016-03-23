//
// Created by Pedro Vanzella on 3/23/16.
//

#ifndef INTELEVATOR_BETTERNEARESTNEIGHBOURDISPATCHER_H
#define INTELEVATOR_BETTERNEARESTNEIGHBOURDISPATCHER_H

#include <memory>
#include "Dispatcher.h"
#include "Elevator.h"
#include "Building.h"
#include "ClientArrival.h"

class BetterNearestNeighbourDispatcher : public Dispatcher {
public:
    explicit BetterNearestNeighbourDispatcher(Building building): Dispatcher(building) {}

    std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const;
};

#endif //INTELEVATOR_BETTERNEARESTNEIGHBOURDISPATCHER_H
