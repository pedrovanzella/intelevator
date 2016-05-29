#pragma once

#include "Scheduler.h"
#include <map>
#include <vector>

class Client;
class Building;
class CostFunction;
class Client;
class Elevator;

class PlanningScheduler : public Scheduler
{
public:
  int schedule(const std::shared_ptr<CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const Client> client);

private:
  std::map<std::shared_ptr<const Elevator>, int>
  calculate(const std::shared_ptr<CostFunction> costFunction,
            const std::shared_ptr<const Building> building,
            int horizon);

  std::vector<std::shared_ptr<Client>>
  getAllWaitingClients(const std::shared_ptr<const Building> b);

  std::map<std::shared_ptr<const Elevator>, int>
  next_step(const std::shared_ptr<CostFunction> costFunction,
            const std::shared_ptr<const Building> building,
            std::vector<std::shared_ptr<Client>> clients,
            std::map<std::shared_ptr<const Elevator>, int> current_costs,
            int horizon);
};
