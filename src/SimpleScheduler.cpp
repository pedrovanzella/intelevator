#include "SimpleScheduler.h"
#include "Building.h"
#include "Client.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Elevator.h"
#include "Floor.h"
#include <limits>

int SimpleScheduler::schedule(
    const std::shared_ptr<const CostFunction> costFunction,
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const ClientArrival> ca) {

  auto elevators = building->getElevators();

  float best_cost = std::numeric_limits<float>::infinity();
  auto the_chosen_one = elevators->front();

  for (auto elevator : *elevators) {
    auto cost = costFunction->calculate(building, elevator, ca->getClient());
    if (cost < best_cost) {
      best_cost = cost;
      the_chosen_one = elevator;
    }
  }

  return the_chosen_one->getNumber();
}
