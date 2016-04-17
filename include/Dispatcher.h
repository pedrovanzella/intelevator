#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include <memory>

class Dispatcher : public std::enable_shared_from_this<Dispatcher> {
public:
  virtual int
  pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                     const std::shared_ptr<const Building> building,
                     const std::shared_ptr<const ClientArrival>) = 0;
};
