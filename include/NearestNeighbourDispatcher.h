//
// Created by Pedro Vanzella on 3/21/16.
//

#ifndef INTELEVATOR_NEARESTNEIGHBOURDISPATCHER_H
#define INTELEVATOR_NEARESTNEIGHBOURDISPATCHER_H

#include <memory>
#include "Dispatcher.h"
#include "Elevator.h"
#include "Building.h"

class NearestNeighbourDispatcher : public Dispatcher {
public:
    explicit NearestNeighbourDispatcher(Building building): Dispatcher(building) {}
    std::shared_ptr<Elevator> pick_next_elevator();
};

#endif //INTELEVATOR_NEARESTNEIGHBOURDISPATCHER_H
