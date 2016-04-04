#include "CostFunctionCreator.h"
#include "DispatcherCreator.h"
#include "easylogging++.h"
#include "Elevator.h"
#include "Floor.h"
#include "Scenario.h"

Scenario::Scenario(YAML::Node scenario)
{
  _name = scenario["name"].as<std::string>();
  _elevators = scenario["elevators"].as<int>();
  _capacity = scenario["elevator_config"]["capacity"].as<int>();

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
  std::shared_ptr<std::vector<std::shared_ptr<const Floor>>> floors(new std::vector<std::shared_ptr<const Floor>>);
  for (int i = 0; i < _population.size(); i++)
  {
    auto f = std::shared_ptr<const Floor>(new Floor(i, _population[i]));
    floors->push_back(f);
  }

  std::shared_ptr<std::vector<std::shared_ptr<const Elevator>>> elevators(new std::vector<std::shared_ptr<const Elevator>>);
  for (int i = 0; i < _elevators; i++)
  {
    auto e = std::shared_ptr<const Elevator>(new Elevator(i, _capacity, floors->at(0)));
    elevators->push_back(e);
  }

  std::shared_ptr<const Dispatcher> dispatcher(DispatcherCreator::create<DummyDispatcher>());
  std::shared_ptr<const CostFunction> costFunction(CostFunctionCreator::create<DummyCostFunction>());

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