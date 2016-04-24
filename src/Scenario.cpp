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
  _floorCount = scenario["floors"].size();

  _dispatcherType = static_cast<DispatcherType>(scenario["dispatcher"].as<int>());
  _costFunctionType = static_cast<CostFunctionType>(scenario["cost_function"].as<int>());
  _seed = scenario["seed"].as<std::string>();

  for (auto it : scenario["floors"]) {
    _population.push_back(it[0].as<int>());
    _lambda.push_back(it[1].as<float>());
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

const std::string Scenario::getName() const { return _name; }

const int Scenario::getElevators() const { return _elevators; }

const int Scenario::getCapacity() const { return _capacity; }

const int Scenario::getFloorCount() const { return _floorCount; }

const std::vector<int> Scenario::getPopulation() const { return _population; }

const std::vector<float> Scenario::getLambda() const { return _lambda; }

const std::vector<std::pair<int, float>> Scenario::getFloors() const {
  return _floors;
}

const std::string Scenario::getSeed() const { return _seed; }

std::shared_ptr<Building> Scenario::createBuilding(const std::shared_ptr<Simulator> simulator) const {
  auto floors = Floor::create(shared_from_this());
  auto elevators = Elevator::create(shared_from_this());
  auto dispatcher = DispatcherCreator::create(_dispatcherType);
  auto costFunction = CostFunctionCreator::create(_costFunctionType);
  auto factories = EventFactory::create(simulator);

  auto building = std::make_shared<Building>(simulator, floors, elevators, factories, dispatcher, costFunction);

  LOG(INFO) << "Created '" << _name << "' scenario with "
            << floors->size() << " floors, "
            << elevators->size() << " elevators, '"
            << Helpers::dispatcherName(_dispatcherType) << "' dispatcher and '"
            << Helpers::costFunctionName(_costFunctionType)
            << "' cost function.";

  return building;
}
