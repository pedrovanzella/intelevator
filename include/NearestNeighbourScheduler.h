#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Scheduler.h"

class NearestNeighbourDispatcher : public Scheduler {
public:
  int pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                         const std::shared_ptr<const Building> building,
                         const std::shared_ptr<const ClientArrival>);
};
