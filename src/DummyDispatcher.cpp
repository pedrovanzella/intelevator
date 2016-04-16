#include "DummyDispatcher.h"

int DummyDispatcher::pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                                        const std::shared_ptr<const Building> building,
                                        const std::shared_ptr<const ClientArrival>)
{
  return 0;
}