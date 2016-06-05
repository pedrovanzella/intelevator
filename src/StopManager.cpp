#include "StopManager.h"
#include "Direction.h"
#include "Elevator.h"
#include "Floor.h"
#include <glog/logging.h>

std::shared_ptr<Elevator> StopManager::hasStop(std::shared_ptr<Floor> floor,
                          Direction direction) const {

  for (auto it : _stops) {
    if (it.first.second != direction) continue;
    for (auto it2 : it.second) {
      if (it2->getNumber() == floor->getNumber())
        return it.first.first;
    }
  }

  return nullptr;
}

void StopManager::set(std::shared_ptr<Floor> floor, Direction direction,
                      std::shared_ptr<Elevator> elevator) {
  _stops[{elevator, direction}].insert(floor);

  LOG(INFO) << "SET _stops[{ " << elevator->getNumber() << ", "
            << Helpers::directionName(direction) << " }] << "
            << floor->getNumber();
}

void StopManager::clear(std::shared_ptr<Floor> floor,
                        std::shared_ptr<Elevator> elevator,
                        Direction direction) {
  _stops[{elevator, direction}].erase(floor);

  LOG(INFO) << "CLEAR _stops[{ " << elevator->getNumber() << ", "
            << Helpers::directionName(direction) << " }] >> "
            << floor->getNumber() << ")";
}

std::set<std::shared_ptr<Floor>>
StopManager::getStops(std::shared_ptr<Elevator> elevator, Direction direction) {
  auto it = _stops.find({elevator, direction});
  if (it == _stops.end())
    return std::set<std::shared_ptr<Floor>>();

  return it->second;
}
