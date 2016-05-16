#include "DummyCostFunction.h"
#include "Building.h"
#include "Client.h"
#include "Elevator.h"

float DummyCostFunction::calculate(
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> c) const {
  return 0.0;
}
