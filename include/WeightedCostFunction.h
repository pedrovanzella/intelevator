#pragma once

#include "CostFunction.h"

class Building;
class Client;
class Elevator;

class WeightedCostFunction : public CostFunction {
public:
  float calculate(const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const Client> c) const;
};
