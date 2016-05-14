#include "DummyCostFunction.h"
#include "Building.h"
#include "ClientArrival.h"
#include "Elevator.h"

float DummyCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const ClientArrival> ca) const {
  return 0.0;
}