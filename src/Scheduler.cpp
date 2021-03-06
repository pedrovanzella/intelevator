#include "Scheduler.h"
#include "Building.h"
#include "Elevator.h"

Scheduler::Scheduler() : _next(0) {}

std::shared_ptr<std::vector<std::shared_ptr<Elevator>>>
Scheduler::getAvailableElevators(const std::shared_ptr<const Building> building,
                int elevatorToExclude) {
  auto elevators = std::make_shared<std::vector<std::shared_ptr<Elevator>>>();
  auto aux = building->getElevators();
  for (int i = _next; i < aux->size(); i++) {
    if (i == elevatorToExclude)
      continue;
    auto elevator = aux->at(i);
    auto copy = std::make_shared<Elevator>(*elevator);
    elevators->push_back(copy);
  }
  for (int i = 0; i < _next; i++) {
    if (i == elevatorToExclude)
      continue;
    auto elevator = aux->at(i);
    auto copy = std::make_shared<Elevator>(*elevator);
    elevators->push_back(copy);
  }
  if (++_next >= aux->size())
    _next = 0;

  return elevators;
}