#include "Scenario.h"
#include "CostFunctionType.h"
#include "SchedulerType.h"
#include "Elevator.h"
#include "Floor.h"
#include "MissingCostFunctionError.h"
#include "MissingSchedulerError.h"
#include <glog/logging.h>
#include <yaml-cpp/yaml.h>

Scenario::Scenario(YAML::Node scenario)
    : _group(scenario["group"].as<std::string>()),
      _name(scenario["name"].as<std::string>()),
      _duration(scenario["duration"].as<int>()),
      _elevators(scenario["elevators"].as<int>()),
      _capacity(scenario["capacity"].as<int>()),
      _floorCount(scenario["floors"].size()),
      _schedulerType(static_cast<SchedulerType>(scenario["scheduler"].as<int>())),
      _costFunctionType(static_cast<CostFunctionType>(scenario["cost_function"].as<int>())),
      _seed(scenario["seed"].as<std::string>()) {
  for (auto it : scenario["floors"]) {
    _floors.push_back(std::make_pair(it[0].as<int>(), it[1].as<float>()));
  }
}

Scenario::~Scenario() {}

std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Scenario::Load(std::string file) {
  YAML::Node config = YAML::LoadFile(file);

  std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> scenarios(new std::vector<std::shared_ptr<const Scenario>>);
  for (auto scenario : config["scenarios"]) {
    auto s = std::make_shared<const Scenario>(scenario);
    scenarios->push_back(s);
  }
  return scenarios;
}

const std::string Scenario::getGroup() const { return _group; }

const std::string Scenario::getName() const { return _name; }

const int Scenario::getDuration() const { return _duration; }

const int Scenario::getElevators() const { return _elevators; }

const int Scenario::getCapacity() const { return _capacity; }

const int Scenario::getFloorCount() const { return _floorCount; }

const SchedulerType Scenario::getSchedulerType() const { return _schedulerType; }

const CostFunctionType Scenario::getCostFunctionType() const { return _costFunctionType; }

const std::vector<std::pair<int, float>> Scenario::getFloors() const {
  return _floors;
}

const std::string Scenario::getSeed() const { return _seed; }
