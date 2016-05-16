#include "PlanningDispatcher.h"
#include "Building.h"
#include "Elevator.h"
#include "Client.h"
#include "Floor.h"
#include "CostFunction.h"
#include <memory>
#include <algorithm>

int PlanningDispatcher::pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
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
PlanningDispatcher::calculate(const std::shared_ptr<const CostFunction> costFunction,
                              const std::shared_ptr<const Building> building,
                              int horizon)
{
  std::map<std::shared_ptr<const Elevator>, int> costs;
  for (auto const e : *building->getElevators()) {
    costs[e] = 0;
  }

  return next_step(costFunction, getAllWaitingClients(building), costs, horizon);
}

std::vector<std::shared_ptr<Client>>
PlanningDispatcher::getAllWaitingClients(const std::shared_ptr<const Building> b)
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
PlanningDispatcher::next_step(const std::shared_ptr<const CostFunction> costFunction,
                              std::vector<std::shared_ptr<Client>> clients,
                              std::map<std::shared_ptr<const Elevator>, int> current_costs,
                              int horizon)
{
  if (horizon <= 0) {
    return current_costs;
  }

  //costFunction->calculate( const std::shared_ptr<const Elevator> elevator, const std::shared_ptr<const Client> c )

  return next_step(costFunction, clients, current_costs, horizon - 1);
}
