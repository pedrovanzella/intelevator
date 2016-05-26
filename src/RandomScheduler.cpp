#include "RandomScheduler.h"

RandomScheduler::RandomScheduler()
 : _seed(std::chrono::high_resolution_clock::now().time_since_epoch().count())
 , _generator(_seed)
{}

int RandomScheduler::pick_next_elevator(
    const std::shared_ptr<const CostFunction> costFunction,
    const std::shared_ptr<const Building> building,
    const std::shared_ptr<const ClientArrival>) {

  if (!_distribution) {
    _distribution = std::make_shared<std::uniform_int_distribution<int>>(0, building->getElevators()->size() - 1);
  }

  return (*_distribution)(_generator);
}