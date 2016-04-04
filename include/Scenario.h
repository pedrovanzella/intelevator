#pragma once

#include <memory>
#include <yaml-cpp/yaml.h>

#include "Building.h"
#include "CostFunctionType.h"
#include "DispatcherType.h"

class Scenario
{
public:
  Scenario(YAML::Node scenario);
  virtual ~Scenario();

  const std::string getName() const;
  std::shared_ptr<Building> createBuilding() const;

  static std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Load(std::string file);

private:
  std::string _name;
  int _elevators;
  int _capacity;
  std::vector<int> _population;
  DispatcherType _dispatcherType;
  CostFunctionType _costFunctionType;
};