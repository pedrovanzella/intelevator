#pragma once

#include <memory>
#include "Building.h"
#include "ClientArrival.h"
#include "Dispatcher.h"
#include "Elevator.h"

// BetterNearestNeighbourDispatcher
class BetterNearestNeighbourDispatcher : public Dispatcher
{
public:
  std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                                                     const std::shared_ptr<const Building> building,
                                                     const std::shared_ptr<const ClientArrival>) const;
};
