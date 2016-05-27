#pragma once

#include "CostFunction.h"

class Building; // forward declaration
class Client;   // forward declaration
class Elevator; // forward declaration

class NearestNeighbourCostFunction : public CostFunction {
public:
  float calculate(const std::shared_ptr<const Building> building,
                  const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const Client> client);
};
