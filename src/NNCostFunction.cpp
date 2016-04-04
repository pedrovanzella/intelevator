#include "NNCostFunction.h"

  float NNCostFunction::calculate(const std::shared_ptr<const Building> building,
                                  const std::shared_ptr<const Elevator> elevator,
                                  const std::shared_ptr<const ClientArrival> ca) const
{
  return abs(ca->getFloor()->getNumber() - elevator->getCurrentFloor()->getNumber());
}