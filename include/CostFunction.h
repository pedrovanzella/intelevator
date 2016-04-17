#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "Elevator.h"
#include <memory>

class CostFunction {
public:
  virtual float
  calculate(const std::shared_ptr<const Building> building,
            const std::shared_ptr<const Elevator> elevator,
            const std::shared_ptr<const ClientArrival> ca) const = 0;
};
