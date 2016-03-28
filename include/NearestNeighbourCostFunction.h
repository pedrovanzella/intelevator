#pragma once

#include "Building.h"
#include "CostFunction.h"
#include "Elevator.h"

class NearestNeighbourCostFunction : public CostFunction
{
public:
  explicit NearestNeighbourCostFunction(std::shared_ptr<Building> b) : CostFunction(b) {}
  float calculate(std::shared_ptr<const Elevator> e, const std::shared_ptr<const ClientArrival> ca) const;
};
