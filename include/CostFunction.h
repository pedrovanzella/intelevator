#pragma once

#include <memory>

class Building;      // forward declaration
class ClientArrival; // forward declaration
class Elevator;      // forward declaration

class CostFunction {
public:
  virtual float
  calculate(const std::shared_ptr<const Building> building,
            const std::shared_ptr<const Elevator> elevator,
            const std::shared_ptr<const ClientArrival> ca) const = 0;
};
