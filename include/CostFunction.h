#pragma once

#include <memory>

class Client;        // forward declaration
class Elevator;      // forward declaration

class CostFunction {
public:
  virtual float
  calculate(const std::shared_ptr<const Elevator> elevator,
            const std::shared_ptr<const Client> c) const = 0;
};
