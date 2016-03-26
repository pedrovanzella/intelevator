//
// Created by Pedro Vanzella on 3/18/16.
//

#ifndef INTELEVATOR_DUMMYDISPATCHER_H
#define INTELEVATOR_DUMMYDISPATCHER_H

#include <memory>
#include "Dispatcher.h"
#include "Elevator.h"
#include "Building.h"
#include "ClientArrival.h"

class DummyDispatcher : public Dispatcher {
public:
    explicit DummyDispatcher(std::shared_ptr<Building> building): Dispatcher(building) {}

    std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const;
};


#endif //INTELEVATOR_DUMMYDISPATCHER_H
