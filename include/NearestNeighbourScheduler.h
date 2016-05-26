#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Scheduler.h"

class NearestNeighbourScheduler : public Scheduler {
public:
  int schedule(const std::shared_ptr<const CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const ClientArrival>);
};
