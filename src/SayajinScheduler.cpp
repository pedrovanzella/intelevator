#include "SayajinScheduler.h"
#include "Building.h"
#include "Client.h"
#include "CostFunction.h"
#include "Elevator.h"
#include "Scenario.h"
#include "Simulator.h"

int SayajinScheduler::schedule(const std::shared_ptr<CostFunction> costFunction,
                               const std::shared_ptr<const Building> building,
                               const std::shared_ptr<const Client> client,
                               const int elevatorToExclude) {

  auto scenario = building->getSimulator()->getScenario();
  auto horizon = scenario->getPlanningHorizon();
  auto elevators = getAvailableElevators(building, elevatorToExclude);
  auto clients = getClients(horizon, client, building);

  std::map<std::shared_ptr<const Elevator>, float> costs;
  for (auto elevator : *elevators) {
    costs[elevator] = 0;
  }

  calculate(costFunction, building, clients, elevators, costs);

  float best_cost = std::numeric_limits<float>::infinity();
  auto the_chosen_one = elevators->front();

  for (auto elevator : *elevators) {
    auto cost = costs[elevator];
    if (cost < best_cost) {
      best_cost = cost;
      the_chosen_one = elevator;
    }
  }

  return the_chosen_one->getNumber();
}

Clients
SayajinScheduler::getClients(const int horizon,
                             const std::shared_ptr<const Client> client,
                             const std::shared_ptr<const Building> building) {
  Clients clients;

  clients.push(client);

  return clients;
}

void SayajinScheduler::calculate(const std::shared_ptr<CostFunction> costFunction,
                                 const std::shared_ptr<const Building> building,
                                 Clients& clients,
                                 Elevators& elevators,
                                 Costs& costs) {
  if (clients.size() == 0) return;

  auto client = clients.front();
  clients.pop();

  for (auto elevator : *elevators) {
    costs[elevator] = costFunction->calculate(building, elevator, client);
  }
}