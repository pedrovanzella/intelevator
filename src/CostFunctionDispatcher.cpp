//
// Created by Pedro Vanzella on 3/26/16.
//

#include <NearestNeighbourCostFunction.h>
#include "CostFunctionDispatcher.h"
#include "Building.h"
#include "DummyCostFunction.h"
#include "NearestNeighbourCostFunction.h"

CostFunctionDispatcher::CostFunctionDispatcher(std::shared_ptr<Building> b) : Dispatcher(b)
{
    auto cf = b->getConfig()->getCostFunction();

    _costFunction = nullptr;

    if (cf == "Dummy") {
        _costFunction = std::shared_ptr<DummyCostFunction>(new DummyCostFunction(b));
    } else if (cf == "NearestNeighbour") {
        _costFunction = std::shared_ptr<NearestNeighbourCostFunction>(new NearestNeighbourCostFunction(b));
    }
}

std::shared_ptr<const Elevator> CostFunctionDispatcher::pick_next_elevator(const std::shared_ptr<const ClientArrival> ca) const
{
    auto elevators = _building->getElevators();

    auto lowest = elevators.front();
    auto lowestCost = _costFunction->calculate(lowest, ca);

    for (auto elevator : elevators) {
        auto cost = _costFunction->calculate(elevator, ca);
        if (cost < lowestCost) {
            lowest = elevator;
            lowestCost = cost;
        }
    }

    return lowest;
}