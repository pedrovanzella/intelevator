#include "PlanningScheduler.h"
#include "CostFunction.h"
#include "Direction.h"
#include "Building.h"
#include "Elevator.h"
#include "Floor.h"
#include "Scenario.h"
#include "Simulator.h"
#include "Status.h"
#include <algorithm>
#include <iostream>

int PlanningScheduler::schedule(const std::shared_ptr<CostFunction> costFunction,
                               const std::shared_ptr<const Building> building,
                               const std::shared_ptr<const Client> client,
                               const int elevatorToExclude) {

  auto simulator = building->getSimulator();
  auto elevators = getAvailableElevators(building, elevatorToExclude);
  auto horizon = simulator->getScenario()->getPlanningHorizon();
  auto clients = getClients(horizon, client, building);

  auto simCopy = std::make_shared<Simulator>(*simulator);
  simCopy->copyBuilding(*simulator->getBuilding());

  auto the_answer_to_life_the_universe_and_everything =
      calculate(simCopy, clients, elevatorToExclude);

  return the_answer_to_life_the_universe_and_everything.first->getNumber();
}

std::pair<std::shared_ptr<Elevator>, float>
PlanningScheduler::calculate(std::shared_ptr<Simulator> simulator,
                            Clients& clients,
                            const int elevatorToExclude) {

  if (clients.empty()) return {nullptr, 0.f};
  auto client = clients.front();
  clients.pop();

  auto elevators = getAvailableElevators(simulator->getBuilding(), elevatorToExclude);

  float best_cost = std::numeric_limits<float>::infinity();
  auto the_chosen_one = elevators->front();

  for (auto elevator : *elevators) {
    auto simCopy = std::make_shared<Simulator>(*simulator);
    simCopy->copyBuilding(*simulator->getBuilding());

    auto buildingCopy = simCopy->getBuilding();
    auto elevatorCopy = buildingCopy->getElevator(elevator->getNumber());

    auto arrivalFloor = client->getArrivalFloor();
    Direction direction = client->getArrivalFloor() < client->getDestination() ? Direction::Up : Direction::Down;

    auto baseCost = 0.f;
    buildingCopy->setStop(arrivalFloor, direction, elevatorCopy);
    while (buildingCopy->mustStop(arrivalFloor, direction, elevatorCopy)) {
      buildingCopy->step();
      baseCost += 1.f;
    }

    auto clientsCopy = copyClients(clients);
    auto futureCost = calculate(simCopy, clientsCopy, elevatorToExclude).second;
    auto cost = baseCost + futureCost;
    if (cost < best_cost) {
      best_cost = cost;
      the_chosen_one = elevator;
    }
  }

  return {the_chosen_one, best_cost};
}

Clients
PlanningScheduler::getClients(const int horizon,
                             const std::shared_ptr<const Client> client,
                             const std::shared_ptr<const Building> building) {
  Clients clients;
  clients.push(client);
  if (horizon > 1) {
    auto globalQueue = getGlobalQueue(horizon, building);
    while(!globalQueue.empty() && clients.size() < horizon) {
      if (client->getId() != globalQueue.top()->getId()) {
        clients.push(globalQueue.top());
      }
      globalQueue.pop();
    }
  }
  return clients;
}

Clients
PlanningScheduler::copyClients(const Clients& clients) {
  Clients shallowCopy(clients);
  Clients deepCopy;

  while (!shallowCopy.empty()) {
    auto clientCopy = std::make_shared<Client>(*shallowCopy.front());
    shallowCopy.pop();
    deepCopy.push(clientCopy);
  }

  return deepCopy;
}

ClientsPriorityQueue PlanningScheduler::getGlobalQueue(
    const int horizon, const std::shared_ptr<const Building> building) {

  std::priority_queue<std::shared_ptr<Client>,
                      std::vector<std::shared_ptr<Client>>, ClientComparator>
      clients;

  for (auto floor : *building->getFloors()) {
    for (auto client : floor->getUpLine(horizon))
      clients.push(client);
    for (auto client : floor->getDownLine(horizon))
      clients.push(client);
  }

  return clients;
}