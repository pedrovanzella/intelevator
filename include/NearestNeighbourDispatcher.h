//
// Created by Pedro Vanzella on 3/21/16.
//

#ifndef INTELEVATOR_NEARESTNEIGHBOURDISPATCHER_H
#define INTELEVATOR_NEARESTNEIGHBOURDISPATCHER_H

#include <memory>
#include "Dispatcher.h"
#include "Elevator.h"
#include "Building.h"
#include "ClientArrival.h"

class NearestNeighbourDispatcher : public Dispatcher {
public:
    explicit NearestNeighbourDispatcher(std::shared_ptr<Building> building): Dispatcher(building) {}

    std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const;
};

#endif //INTELEVATOR_NEARESTNEIGHBOURDISPATCHER_H
