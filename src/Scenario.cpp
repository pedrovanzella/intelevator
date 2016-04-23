#include <string>

#include "CostFunctionCreator.h"
#include "DispatcherCreator.h"
#include "Elevator.h"
#include "Floor.h"
#include "MissingCostFunctionError.h"
#include "MissingDispatcherError.h"
#include "RandomDispatcher.h"
#include "Scenario.h"
#include <glog/logging.h>

Scenario::Scenario(YAML::Node scenario) {
  _name = scenario["name"].as<std::string>();
  _elevators = scenario["elevators"].as<int>();
  _capacity = scenario["elevator_config"]["capacity"].as<int>();
  _dispatcherType = static_cast<DispatcherType>(scenario["dispatcher"].as<int>());
  _costFunctionType = static_cast<CostFunctionType>(scenario["cost_function"].as<int>());
  _seed = scenario["seed"].as<std::string>();

  for (auto it : scenario["population"]) {
    _population.push_back(it.as<int>());
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

const std::string Scenario::getName() const { return _name; }

const int Scenario::getElevators() const { return _elevators; }

const int Scenario::getCapacity() const { return _capacity; }

const std::vector<int> Scenario::getPopulation() const { return _population; }

const std::string Scenario::getSeed() const { return _seed; }

std::shared_ptr<Building> Scenario::createBuilding(const std::shared_ptr<Simulator> simulator) const {
  auto floors = Floor::createFloors(shared_from_this());
  auto elevators = Elevator::createElevators(shared_from_this());
  auto dispatcher = DispatcherCreator::create(_dispatcherType);
  auto costFunction = CostFunctionCreator::create(_costFunctionType);

  auto building = std::make_shared<Building>(simulator, floors, elevators, dispatcher, costFunction);

  LOG(INFO) << "Created '" << _name << "' scenario with "
            << floors->size() << " floors, "
            << elevators->size() << " elevators, '"
            << Helpers::dispatcherName(_dispatcherType) << "' dispatcher and '"
            << Helpers::costFunctionName(_costFunctionType)
            << "' cost function.";

  return building;
}
