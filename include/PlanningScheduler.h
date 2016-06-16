#pragma once

#include "Client.h"
#include "Scheduler.h"
#include <map>
#include <queue>
#include <vector>

class Building;
class CostFunction;
class Simulator;

class ClientComparator {
public:
  bool operator()(std::shared_ptr<const Client> lhs,
                  std::shared_ptr<const Client> rhs) const {
    return lhs->getCreateTime() < rhs->getCreateTime();
  }
};

using Clients = std::queue<std::shared_ptr<const Client>>;
using Elevators = std::shared_ptr<std::vector<std::shared_ptr<Elevator>>>;
using ClientsPriorityQueue =
    std::priority_queue<std::shared_ptr<Client>,
                        std::vector<std::shared_ptr<Client>>,
                        ClientComparator>;

class PlanningScheduler : public Scheduler {
public:
  int schedule(const std::shared_ptr<CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const Client> client,
               const int elevatorToExclude = -1);

private:
  std::pair<std::shared_ptr<Elevator>, float>
  calculate(std::shared_ptr<Simulator> simulator,
            Clients& clients,
            const int elevatorToExclude);

  Clients getClients(const int horizon,
                     const std::shared_ptr<const Client> client,
                     const std::shared_ptr<const Building> building);

  Clients copyClients(const Clients& clients);

  ClientsPriorityQueue
  getGlobalQueue(const int horizon,
                 const std::shared_ptr<const Building> building);
};
