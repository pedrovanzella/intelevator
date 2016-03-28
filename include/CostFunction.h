#pragma once

#include <memory>
#include "ClientArrival.h"

class Building; // forward declaration
class Elevator; // forward declaration

class CostFunction
{
public:
  CostFunction(std::shared_ptr<Building> b);
  virtual ~CostFunction() {}
  virtual float calculate(std::shared_ptr<const Elevator>, const std::shared_ptr<const ClientArrival> ca) const = 0;

protected:
  std::shared_ptr<Building> _building;
};
