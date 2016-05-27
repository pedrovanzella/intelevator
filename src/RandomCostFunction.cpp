#include "RandomCostFunction.h"

RandomCostFunction::RandomCostFunction()
 : _seed("54TH7hboAG1iOsDIDhJp")
 , _seed_seq(_seed.begin(), _seed.end())
 , _generator(_seed_seq)
 , _distribution(0.0, 1.0)
{}

float RandomCostFunction::calculate(
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const Elevator> elevator,
    const std::shared_ptr<const Client> client) {

  return _distribution(_generator);
}
