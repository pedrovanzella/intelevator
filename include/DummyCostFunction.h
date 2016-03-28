#pragma once

#include "Building.h"
#include "CostFunction.h"
#include "Elevator.h"

class DummyCostFunction : public CostFunction
{
public:
  explicit DummyCostFunction(std::shared_ptr<Building> b) : CostFunction(b) {}
  float calculate(std::shared_ptr<const Elevator> e, const std::shared_ptr<const ClientArrival> ca) const;
};
