#pragma once

#include "Building.h"
#include "CostFunctionType.h"
#include "DispatcherType.h"
#include <memory>
#include <yaml-cpp/yaml.h>

class Scenario : public std::enable_shared_from_this<Scenario> {
public:
  Scenario(YAML::Node scenario);
  virtual ~Scenario();

  static std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Load(std::string file);

  const std::string getName() const;
  const std::vector<int> getPopulation() const;

  std::shared_ptr<Building> createBuilding(const std::shared_ptr<Simulator> simulator) const;

private:
  std::string _name;
  int _elevators;
  int _capacity;
  std::vector<int> _population;
  DispatcherType _dispatcherType;
  CostFunctionType _costFunctionType;

  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> createFloors() const;
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> createElevators() const;
  std::shared_ptr<Dispatcher> createDispatcher() const;
  std::shared_ptr<const CostFunction> createCostFunction() const;
};