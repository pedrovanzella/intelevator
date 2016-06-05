#include "StopManager.h"
#include "Direction.h"
#include "Elevator.h"
#include "Floor.h"
#include <glog/logging.h>

bool StopManager::hasStop(std::shared_ptr<Floor> floor,
                          Direction direction) {

  // for (auto it : _stopsPerElevator) {
  //   if (it.first.second != direction) continue;
  //   for (auto it2 : it.second) {
  //     if (it2->getNumber() == floor->getNumber())
  //       return true;
  //   }
  // }

  return !_stopsPerFloor[{floor, direction}].empty();

  // return false;
}

void StopManager::set(std::shared_ptr<Floor> floor, Direction direction,
                      std::shared_ptr<Elevator> elevator) {
  _stopsPerElevator[{elevator, direction}].insert(floor);
  _stopsPerFloor[{floor, direction}].insert(elevator);

  LOG(INFO) << "SET _stopsPerElevator[{ " << elevator->getNumber() << ", "
            << Helpers::directionName(direction) << " }] << "
            << floor->getNumber();
}

void StopManager::clear(std::shared_ptr<Floor> floor,
                        std::shared_ptr<Elevator> elevator,
                        Direction direction) {
  _stopsPerElevator[{elevator, direction}].erase(floor);
  _stopsPerFloor[{floor, direction}].erase(elevator);

  LOG(INFO) << "CLEAR _stopsPerElevator[{ " << elevator->getNumber() << ", "
            << Helpers::directionName(direction) << " }] >> "
            << floor->getNumber() << ")";
}

std::set<std::shared_ptr<Floor>>
StopManager::getStops(std::shared_ptr<Elevator> elevator, Direction direction) {
  auto it = _stopsPerElevator.find({elevator, direction});
  if (it == _stopsPerElevator.end())
    return std::set<std::shared_ptr<Floor>>();

  return it->second;
}
