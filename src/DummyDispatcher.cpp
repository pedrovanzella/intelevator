#include "DummyDispatcher.h"

std::shared_ptr<const Elevator> DummyDispatcher::pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                                                                    const std::shared_ptr<const Building> building,
                                                                    const std::shared_ptr<const ClientArrival>) const
{
  return nullptr;
}