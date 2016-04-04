#pragma once

#include "Building.h"
#include "CostFunction.h"
#include "Elevator.h"

class NNCostFunction : public CostFunction
{
public:
  float calculate(const std::shared_ptr<const Building> building,
                  const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const ClientArrival> ca) const;
};
