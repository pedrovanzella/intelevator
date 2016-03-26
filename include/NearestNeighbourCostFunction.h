//
// Created by Pedro Vanzella on 3/26/16.
//

#ifndef INTELEVATOR_NEARESTNEIGHBOURCOSTFUNCTION_H
#define INTELEVATOR_NEARESTNEIGHBOURCOSTFUNCTION_H

#include "CostFunction.h"
#include "Building.h"
#include "Elevator.h"

class NearestNeighbourCostFunction : public CostFunction
{
public:
    explicit NearestNeighbourCostFunction(std::shared_ptr<Building> b) : CostFunction(b) {}

    float calculate(std::shared_ptr<const Elevator> e, const std::shared_ptr<const ClientArrival> ca) const;
};

#endif //INTELEVATOR_NEARESTNEIGHBOURCOSTFUNCTION_H
