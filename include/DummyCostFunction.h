//
// Created by Pedro Vanzella on 3/26/16.
//

#ifndef INTELEVATOR_DUMMYCOSTFUNCTION_H
#define INTELEVATOR_DUMMYCOSTFUNCTION_H
#include "CostFunction.h"
#include "Building.h"

class DummyCostFunction : public CostFunction
{
public:
    explicit DummyCostFunction(std::shared_ptr<Building> b) : CostFunction(b) {}

    float calculate() const;
};

#endif //INTELEVATOR_DUMMYCOSTFUNCTION_H
