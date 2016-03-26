//
// Created by Pedro Vanzella on 3/26/16.
//

#include "NearestNeighbourCostFunction.h"

float NearestNeighbourCostFunction::calculate(std::shared_ptr<const Elevator> e, const std::shared_ptr<const ClientArrival> ca) const
{
    return abs(ca->getFloor()->getNumber() - e->getCurrentFloor()->getNumber());
}