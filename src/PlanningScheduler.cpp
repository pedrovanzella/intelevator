#include "PlanningScheduler.h"
#include "Building.h"
#include "Elevator.h"
#include "Client.h"
#include "Floor.h"
#include "CostFunction.h"
#include <memory>
#include <algorithm>

int PlanningScheduler::schedule(const std::shared_ptr<const CostFunction> costFunction,
                                const std::shared_ptr<const Building> building,
                                const std::shared_ptr<const ClientArrival> ca)
{
  auto costs = calculate(costFunction, building, 5);
  std::shared_ptr<const Elevator> lowestCost = building->getElevators()->front();

  for (auto const c : costs) {
    if (c.second < costs[lowestCost]) {
        lowestCost = c.first;
      }
  }

  return lowestCost->getNumber();
}

std::map<std::shared_ptr<const Elevator>, int>
PlanningScheduler::calculate(const std::shared_ptr<const CostFunction> costFunction,
                              const std::shared_ptr<const Building> building,
                              int horizon)
{
  std::map<std::shared_ptr<const Elevator>, int> costs;
  for (auto const e : *building->getElevators()) {
    costs[e] = 0;
  }

  return next_step(costFunction, building, getAllWaitingClients(building), costs, horizon);
}

std::vector<std::shared_ptr<Client>>
PlanningScheduler::getAllWaitingClients(const std::shared_ptr<const Building> b)
{
  std::vector<std::shared_ptr<Client>> all;

  for (auto f : *b->getFloors()) {
    // Get all clients on this floor and add them to all
    for (auto c : f->getUpLine()) {
      all.push_back(c);
    }
    for (auto c : f->getDownLine()) {
      all.push_back(c);
    }
  }

  // sort all
  std::sort(all.begin(), all.end(), [](std::shared_ptr<Client> c1, std::shared_ptr<Client> c2) {
      return c1->getCreateTime() > c2->getCreateTime();
    });

  return all;
}

std::map<std::shared_ptr<const Elevator>, int>
PlanningScheduler::next_step(const std::shared_ptr<const CostFunction> costFunction,
  const std::shared_ptr<const Building> building,
                              std::vector<std::shared_ptr<Client>> clients,
                              std::map<std::shared_ptr<const Elevator>, int> current_costs,
                              int horizon)
{
  if (horizon <= 0) {
    return current_costs;
  }

  for (auto m : current_costs) {
    // m.first is the elevator
    std::shared_ptr<Client> lowestCostClient = nullptr;
    auto lowestCost = 0;

    // find out the lowest cost for this elevator
    for (auto c : clients) {
      auto cost = costFunction->calculate(building, m.first, c);
      if (cost < lowestCost) {
        lowestCost = cost;
        lowestCostClient = c;
      }
    }
    current_costs[m.first] += lowestCost;
    // remove client from list
    clients.erase(std::remove(clients.begin(), clients.end(), lowestCostClient), clients.end());
  }

  return next_step(costFunction, building, clients, current_costs, horizon - 1);
}
