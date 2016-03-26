//
// Created by Pedro Vanzella on 3/26/16.
//

#include "DummyCostFunction.h"

float DummyCostFunction::calculate(std::shared_ptr<const Elevator> e, const std::shared_ptr<const ClientArrival> ca) const
{
    return 0.0;
}