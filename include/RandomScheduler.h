#pragma once

#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Scheduler.h"
#include <chrono>
#include <memory>
#include <random>
#include <string>

class RandomScheduler : public Scheduler {
public:
  int schedule(const std::shared_ptr<const CostFunction> costFunction,
               const std::shared_ptr<const Building> building,
               const std::shared_ptr<const ClientArrival>);

  RandomScheduler();

private:
  std::string _seed;
  std::seed_seq _seed_seq;
  std::default_random_engine _generator;
  std::shared_ptr<std::uniform_int_distribution<int>> _distribution;
};
