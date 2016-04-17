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

std::shared_ptr<Building> Scenario::createBuilding(const std::shared_ptr<Simulator> simulator) const {
  auto floors = Floor::createFloors(shared_from_this());
  auto elevators = createElevators();
  auto dispatcher = createDispatcher();
  auto costFunction = createCostFunction();

  auto building = std::make_shared<Building>(simulator, floors, elevators, dispatcher, costFunction);

  LOG(INFO) << "Created '" << _name << "' scenario with "
            << floors->size() << " floors, "
            << elevators->size() << " elevators, '"
            << Helpers::dispatcherName(_dispatcherType) << "' dispatcher and '"
            << Helpers::costFunctionName(_costFunctionType)
            << "' cost function.";

  return building;
}

std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Scenario::createElevators() const {
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators(new std::vector<std::shared_ptr<Elevator>>);

  for (int i = 0; i < _elevators; i++) {
    auto e = std::make_shared<Elevator>(i, _capacity, 0);
    elevators->push_back(e);
  }

  return elevators;
}

std::shared_ptr<Dispatcher> Scenario::createDispatcher() const {
  switch (_dispatcherType) {
  case DispatcherType::Dummy:
    return DispatcherCreator::create<DummyDispatcher>();
  case DispatcherType::Random:
    return DispatcherCreator::create<RandomDispatcher>();
  case DispatcherType::NearestNeighbour:
    return DispatcherCreator::create<NearestNeighbourDispatcher>();
  case DispatcherType::BetterNearestNeighbour:
    return DispatcherCreator::create<BetterNearestNeighbourDispatcher>();
  default:
    throw MissingDispatcherError(std::to_string((int)_dispatcherType));
  }
}

std::shared_ptr<const CostFunction> Scenario::createCostFunction() const {
  switch (_costFunctionType) {
  case CostFunctionType::Dummy:
    return CostFunctionCreator::create<DummyCostFunction>();
  case CostFunctionType::NearestNeighbour:
    return CostFunctionCreator::create<NearestNeighbourCostFunction>();
  default:
    throw MissingCostFunctionError(std::to_string((int)_costFunctionType));
  }
}