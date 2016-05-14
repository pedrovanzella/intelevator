#pragma once

#include "CostFunction.h"

class Building;
class ClientArrival;
class Elevator;

class DummyCostFunction : public CostFunction {
public:
  float calculate(const std::shared_ptr<const Building> building,
                  const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const ClientArrival> ca) const;
};
