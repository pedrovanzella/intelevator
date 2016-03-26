//
// Created by Pedro Vanzella on 3/26/16.
//

#ifndef INTELEVATOR_COSTFUNCTIONDISPATCHER_H
#define INTELEVATOR_COSTFUNCTIONDISPATCHER_H
#include "Dispatcher.h"
#include "CostFunction.h"

class CostFunctionDispatcher : public Dispatcher
{
    explicit CostFunctionDispatcher(std::shared_ptr<Building> b);

    std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const;

private:
    std::shared_ptr<CostFunction> _costFunction;
};

#endif //INTELEVATOR_COSTFUNCTIONDISPATCHER_H
