#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Scheduler.h"
#include <chrono>
#include <memory>
#include <random>

class RandomDispatcher : public Scheduler {
public:
  int pick_next_elevator(const std::shared_ptr<const CostFunction> costFunction,
                         const std::shared_ptr<const Building> building,
                         const std::shared_ptr<const ClientArrival>);

  RandomDispatcher();

private:
  unsigned _seed;
  std::default_random_engine _generator;
  std::shared_ptr<std::uniform_int_distribution<int>> _distribution;
};
