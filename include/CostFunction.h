//
// Created by Pedro Vanzella on 3/26/16.
//

#ifndef INTELEVATOR_COSTFUNCTION_H
#define INTELEVATOR_COSTFUNCTION_H
#include <memory>

class Building;

class CostFunction
{
public:
    CostFunction(Building b);

    virtual ~CostFunction() {}

    virtual float calculate() const = 0;
protected:
    std::shared_ptr<Building> _building;
};

#endif //INTELEVATOR_COSTFUNCTION_H
