#include "Scenario.h"
#include "CostFunctionType.h"
#include "SchedulerType.h"
#include "Elevator.h"
#include "Floor.h"
#include "MissingCostFunctionError.h"
#include "MissingSchedulerError.h"
#include <glog/logging.h>
#include <yaml-cpp/yaml.h>

Scenario::Scenario(std::string name, int duration, int elevators, int capacity,
                   int floorCount, SchedulerType schedulerType,
                   CostFunctionType costFunctionType, std::string seed,
                   std::vector<std::pair<int, float>> floors, std::time_t timestamp)
    : _name(name), _duration(duration), _elevators(elevators),
      _capacity(capacity), _floorCount(floorCount),
      _schedulerType(schedulerType), _costFunctionType(costFunctionType),
      _seed(seed), _floors(floors), _timestamp(timestamp) {}

Scenario::~Scenario() {}

std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Scenario::Load(std::string file) {
  YAML::Node config = YAML::LoadFile(file);

  std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> scenarios(new std::vector<std::shared_ptr<const Scenario>>);
  for (auto scenario : config["scenarios"]) {

    auto name = scenario["name"].as<std::string>();
    auto duration = scenario["duration"].as<int>();
    auto elevators = scenario["elevators"].as<int>();
    auto capacity = scenario["capacity"].as<int>();
    auto floorCount = scenario["floors"].size();
    auto seed = scenario["seed"].as<std::string>();
    auto timestamp = std::time(nullptr);

    std::vector<std::pair<int, float>> floors;
    for (auto it : scenario["floors"]) {
      floors.push_back(std::make_pair(it[0].as<int>(), it[1].as<float>()));
    }

    for (auto it : scenario["scheduler"]) {
      auto schedulerType = static_cast<SchedulerType>(it.as<int>());

      for (auto it : scenario["cost_function"]) {
        auto costFunctionType = static_cast<CostFunctionType>(it.as<int>());

        auto s = std::make_shared<const Scenario>(name, duration, elevators, capacity, floorCount, schedulerType, costFunctionType, seed, floors, timestamp);
        scenarios->push_back(s);
      }
    }
  }
  return scenarios;
}

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

const std::string Scenario::getBasePath() const {
  auto timestamp = _timestamp;
  std::tm* ptm = std::localtime(&timestamp);
  char buffer[32];
  std::strftime(buffer, 32, "%Y%m%d_%H%M%S", ptm);

  std::string path = "output/" + _name + "_" + buffer + "/";
  std::string command = "mkdir -p \"" + path + "\"";
  system(command.c_str());
  return path;
}

const std::string Scenario::getPath() const {
  std::string path = getBasePath() +
      Helpers::schedulerName(_schedulerType) + "_" +
      Helpers::costFunctionName(_costFunctionType) + "/";
  std::string command = "mkdir -p \"" + path + "\"";
  system(command.c_str());
  return path;
}