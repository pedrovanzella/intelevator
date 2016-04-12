#include <string>

#include "CostFunctionCreator.h"
#include "DispatcherCreator.h"
#include <glog/logging.h>
#include "Elevator.h"
#include "Floor.h"
#include "MissingCostFunctionError.h"
#include "MissingDispatcherError.h"
#include "Scenario.h"

Scenario::Scenario(YAML::Node scenario)
{
  _name = scenario["name"].as<std::string>();
  _elevators = scenario["elevators"].as<int>();
  _capacity = scenario["elevator_config"]["capacity"].as<int>();
  _dispatcherType = static_cast<DispatcherType>(scenario["dispatcher"].as<int>());
  _costFunctionType = static_cast<CostFunctionType>(scenario["cost_function"].as<int>());

  for (auto it : scenario["population"])
  {
    _population.push_back(it.as<int>());
  }
}

Scenario::~Scenario()
{}

const std::string Scenario::getName() const
{
  return _name;
}

std::shared_ptr<Building> Scenario::createBuilding() const
{
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors(new std::vector<std::shared_ptr<Floor>>);
  for (int i = 0; i < _population.size(); i++)
  {
    auto f = std::shared_ptr<Floor>(new Floor(i, _population[i]));
    floors->push_back(f);
  }

  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators(new std::vector<std::shared_ptr<Elevator>>);
  for (int i = 0; i < _elevators; i++)
  {
    auto e = std::make_shared<Elevator>(i, _capacity, floors->front()->getNumber());
    elevators->push_back(e);
  }

  std::shared_ptr<const Dispatcher> dispatcher;
  switch(_dispatcherType)
  {
    case DispatcherType::Dummy:
      dispatcher = DispatcherCreator::create<DummyDispatcher>();
      break;
    case DispatcherType::NearestNeighbour:
      dispatcher = DispatcherCreator::create<NearestNeighbourDispatcher>();
      break;
    case DispatcherType::BetterNearestNeighbour:
      dispatcher = DispatcherCreator::create<BetterNearestNeighbourDispatcher>();
      break;
    default:
      throw MissingDispatcherError(std::to_string((int)_dispatcherType));
  }

  std::shared_ptr<const CostFunction> costFunction;
  switch(_costFunctionType)
  {
    case CostFunctionType::Dummy:
      costFunction = CostFunctionCreator::create<DummyCostFunction>();
      break;
    case CostFunctionType::NearestNeighbour:
      costFunction = CostFunctionCreator::create<NearestNeighbourCostFunction>();
      break;
    default:
      throw MissingCostFunctionError(std::to_string((int)_costFunctionType));
  }

  LOG(INFO) << "Created '" << _name << "' scenario with "
            << floors->size() << " floors, "
            << elevators->size() << " elevators, '"
            << Helpers::dispatcherName(_dispatcherType) << "' dispatcher and '"
            << Helpers::costFunctionName(_costFunctionType) << "' cost function.";

  std::shared_ptr<Building> b(new Building(floors, elevators, dispatcher, costFunction));
  return b;
}

std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Scenario::Load(std::string file)
{
  YAML::Node config = YAML::LoadFile(file);

  std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> scenarios(new std::vector<std::shared_ptr<const Scenario>>);
  for (auto scenario : config["scenarios"])
  {
    auto s = std::shared_ptr<const Scenario>(new Scenario(scenario));
    scenarios->push_back(s);
  }
  return scenarios;
}