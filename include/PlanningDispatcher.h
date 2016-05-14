#pragma once

#include "Dispatcher.h"
#include <map>

class PlanningDispatcher : public Dispatcher
{
public:
  int pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                         const std::shared_ptr<const Building> building,
                         const std::shared_ptr<const ClientArrival>);

private:
  std::map<int, int> calculate(const std::shared_ptr<const CostFunction> costFunction,
                               const std::shared_ptr<const Building> building,
                               int horizon);
  std::map<int, int> next_step(const std::shared_ptr<const CostFunction> costFunction,
                               const std::shared_ptr<const Building> building,
                               std::map<int, int> current_costs,
                               int horizon);
};
