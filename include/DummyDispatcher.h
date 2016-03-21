//
// Created by Pedro Vanzella on 3/18/16.
//

#ifndef INTELEVATOR_DUMMYDISPATCHER_H
#define INTELEVATOR_DUMMYDISPATCHER_H

#include <memory>
#include "Dispatcher.h"
#include "Elevator.h"
#include "Building.h"

class DummyDispatcher : public Dispatcher {
public:
    explicit DummyDispatcher(Building building): Dispatcher(building) {}
    std::shared_ptr<Elevator> pick_next_elevator();
};


#endif //INTELEVATOR_DUMMYDISPATCHER_H
