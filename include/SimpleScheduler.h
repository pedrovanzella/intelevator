#pragma once

#include "Scheduler.h"

class Building;     // forward declaration
class Client;       // forward declaration
class CostFunction; // forward declaration
class Elevator;     // forward declaration

class SimpleScheduler : public Scheduler {
public:
  SimpleScheduler();
  int schedule(const std::shared_ptr<CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const Client> client,
               const int elevatorToExclude = -1);
};
