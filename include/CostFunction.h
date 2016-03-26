//
// Created by Pedro Vanzella on 3/26/16.
//

#ifndef INTELEVATOR_COSTFUNCTION_H
#define INTELEVATOR_COSTFUNCTION_H
#include <memory>
#include "ClientArrival.h"

class Building;
class Elevator;

class CostFunction
{
public:
    CostFunction(std::shared_ptr<Building> b);

    virtual ~CostFunction() {}

    virtual float calculate(std::shared_ptr<const Elevator>, const std::shared_ptr<const ClientArrival> ca) const = 0;
protected:
    std::shared_ptr<Building> _building;
};

#endif //INTELEVATOR_COSTFUNCTION_H
