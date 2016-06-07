#pragma once

#include "Scheduler.h"
#include <map>
#include <queue>
#include <vector>

class Client;
class Building;
class CostFunction;

using Clients = std::queue<std::shared_ptr<const Client>>;
using Elevators = std::shared_ptr<std::vector<std::shared_ptr<Elevator>>>;
using Costs = std::map<std::shared_ptr<const Elevator>, float>;

class SayajinScheduler : public Scheduler {
public:
  int schedule(const std::shared_ptr<CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const Client> client,
               const int elevatorToExclude = -1);

private:
  Clients getClients(const int horizon,
                     const std::shared_ptr<const Client> client,
                     const std::shared_ptr<const Building> building);

  std::pair<std::shared_ptr<Elevator>, float>
  calculate(const std::shared_ptr<CostFunction> costFunction,
            const std::shared_ptr<const Building> building,
            Elevators elevators,
            Clients clients);
};
