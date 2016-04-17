#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Elevator.h"

class DummyCostFunction : public CostFunction {
public:
  float calculate(const std::shared_ptr<const Building> building,
                  const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const ClientArrival> ca) const;
};
