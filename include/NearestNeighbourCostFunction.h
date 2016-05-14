#pragma once

#include "CostFunction.h"

class Building;
class Client;
class Elevator;

class NearestNeighbourCostFunction : public CostFunction {
public:
  float calculate(const std::shared_ptr<const Building> building,
                  const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const Client> c) const;
};
