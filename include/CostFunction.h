#pragma once

#include <memory>

class Building;
class ClientArrival;
class Elevator;

class CostFunction {
public:
  virtual float
  calculate(const std::shared_ptr<const Building> building,
            const std::shared_ptr<const Elevator> elevator,
            const std::shared_ptr<const ClientArrival> ca) const = 0;
};
