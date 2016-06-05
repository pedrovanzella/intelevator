#pragma once

#include "Scheduler.h"

class Client;
class Building;
class CostFunction;

class SayajinScheduler : public Scheduler {
public:
  int schedule(const std::shared_ptr<CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const Client> client,
               const int elevatorToExclude = -1);
};
