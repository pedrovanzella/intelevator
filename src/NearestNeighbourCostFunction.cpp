#include "NearestNeighbourCostFunction.h"

  float NearestNeighbourCostFunction::calculate(const std::shared_ptr<const Building> building,
                                  const std::shared_ptr<const Elevator> elevator,
                                  const std::shared_ptr<const ClientArrival> ca) const
{
  return abs(ca->getClient()->getArrivalFloor() - elevator->getLocation());
}