#pragma once

#include "Scheduler.h"

class Building;      // forward declaration
class ClientArrival; // forward declaration
class CostFunction;  // forward declaration

class DummyScheduler : public Scheduler {
public:
  int pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                         const std::shared_ptr<const Building> building,
                         const std::shared_ptr<const ClientArrival>);
};
