#pragma once

#include "CostFunction.h"
#include <memory>
#include <random>
#include <string>


class Building;      // forward declaration
class Client;        // forward declaration
class Elevator;      // forward declaration

class RandomCostFunction : public CostFunction {
public:
  RandomCostFunction();

  float calculate(const std::shared_ptr<const Building> building,
                  const std::shared_ptr<const Elevator> elevator,
                  const std::shared_ptr<const Client> client);

private:
  std::string _seed;
  std::seed_seq _seed_seq;
  std::default_random_engine _generator;
  std::shared_ptr<std::uniform_real_distribution<double>> _distribution;
};
