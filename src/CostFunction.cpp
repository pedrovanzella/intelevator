//
// Created by Pedro Vanzella on 3/26/16.
//
#include "CostFunction.h"
#include "Building.h"

CostFunction::CostFunction(Building b)
{
    _building = std::make_shared<Building>(b);
}
