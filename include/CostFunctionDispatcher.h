#pragma once

#include "CostFunction.h"
#include "Dispatcher.h"

class CostFunctionDispatcher : public Dispatcher
{
  explicit CostFunctionDispatcher(std::shared_ptr<Building> b);
  std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const;

private:
  std::shared_ptr<CostFunction> _costFunction;
};
