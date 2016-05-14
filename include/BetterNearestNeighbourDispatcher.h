#pragma once

#include "Dispatcher.h"

class CostFunction;
class Building;
class ClientArrival;

class BetterNearestNeighbourDispatcher : public Dispatcher
{
public:
  int pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                         const std::shared_ptr<const Building> building,
                         const std::shared_ptr<const ClientArrival>);
};
