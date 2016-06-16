#include "RandomCostFunction.h"
#include "Building.h"
#include "Simulator.h"
#include "Scenario.h"

RandomCostFunction::RandomCostFunction()
 : _seed("54TH7hboAG1iOsDIDhJp")
 , _seed_seq(_seed.begin(), _seed.end())
 , _generator(_seed_seq)
{}

float RandomCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) {

  if (_distribution == nullptr) {
    auto number_of_floors = building->getSimulator()->getScenario()->getFloorCount();
    _distribution = std::make_shared<std::uniform_real_distribution<double>>(0.0, number_of_floors);
  }

  auto dist = *_distribution;
  return dist(_generator);
}
