#include "DummyScheduler.h"
#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"

int DummyScheduler::schedule(const std::shared_ptr<CostFunction> costFunction,
                             const std::shared_ptr<const Building> building,
                             const std::shared_ptr<const ClientArrival>)
{
  return 0;
}