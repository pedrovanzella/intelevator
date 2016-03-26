//
// Created by Pedro Vanzella on 3/26/16.
//
#include "CostFunction.h"
#include "Building.h"

CostFunction::CostFunction(std::shared_ptr<Building> b)
{
    _building = b;
}
