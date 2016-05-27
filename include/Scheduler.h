#pragma once

#include <memory>

class Building;      // forward declaration
class ClientArrival; // forward declaration
class CostFunction;  // forward declaration

class Scheduler : public std::enable_shared_from_this<Scheduler> {
public:
  virtual int
  schedule(const std::shared_ptr<CostFunction> costFunction,
           const std::shared_ptr<const Building> building,
           const std::shared_ptr<const ClientArrival>) = 0;
};
