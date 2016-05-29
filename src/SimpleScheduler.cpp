#include "SimpleScheduler.h"
#include "Building.h"
#include "Client.h"
#include "CostFunction.h"
#include "Elevator.h"
#include "Floor.h"
#include <limits>

SimpleScheduler::SimpleScheduler() : _next(0) {}

int SimpleScheduler::schedule(
    const std::shared_ptr<CostFunction> costFunction,
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Client> client) {

  auto elevators = std::make_shared<std::vector<std::shared_ptr<Elevator>>>();
  auto aux = building->getElevators();
  for (int i = _next; i < aux->size(); i++)
    elevators->push_back(aux->at(i));
  for (int i = 0; i < _next; i++)
    elevators->push_back(aux->at(i));
  if (++_next >= aux->size()) _next = 0;

  float best_cost = std::numeric_limits<float>::infinity();
  auto the_chosen_one = elevators->front();

  for (auto elevator : *elevators) {
    auto cost = costFunction->calculate(building, elevator, client);
    if (cost < best_cost) {
      best_cost = cost;
      the_chosen_one = elevator;
    }
  }

  return the_chosen_one->getNumber();
}
