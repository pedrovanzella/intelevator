#pragma once

#include <memory>

class Building;
class Client;
class Elevator;

class CostFunction {
public:
  virtual float
  calculate(const std::shared_ptr<const Building> building,
            const std::shared_ptr<const Elevator> elevator,
            const std::shared_ptr<const Client> c) const = 0;
};
