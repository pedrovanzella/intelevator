#include "StopManager.h"
#include "Direction.h"
#include "Elevator.h"
#include "Floor.h"
#include <glog/logging.h>

StopManager::StopManager() {}

StopManager::StopManager(const StopManager& stopManager, const std::vector<std::shared_ptr<Elevator>> elevators) {
  for (auto elevator : elevators) {
    for (auto floor : stopManager.getStops(elevator, Direction::Up)) {
      this->set(floor, Direction::Up, elevator);
    }
    for (auto floor : stopManager.getStops(elevator, Direction::Down)) {
      this->set(floor, Direction::Down, elevator);
    }
  }
}

bool StopManager::hasStop(std::shared_ptr<Floor> floor,
                          Direction direction) {
  return !_stopsPerFloor[{floor, direction}].empty();
}

void StopManager::set(std::shared_ptr<Floor> floor, Direction direction,
                      std::shared_ptr<Elevator> elevator) {
  _stopsPerElevator[{elevator, direction}].insert(floor);
  _stopsPerFloor[{floor, direction}].insert(elevator);

  LOG(INFO) << "SET _stopsPerElevator[{ e=" << elevator->getNumber() << ", d="
            << Helpers::directionName(direction) << ", f=" << floor->getNumber() << "}]";
}

void StopManager::clear(std::shared_ptr<Floor> floor,
                        std::shared_ptr<Elevator> elevator,
                        Direction direction) {
  _stopsPerElevator[{elevator, direction}].erase(floor);
  _stopsPerFloor[{floor, direction}].erase(elevator);

  LOG(INFO) << "CLEAR _stopsPerElevator[{ e=" << elevator->getNumber() << ", d="
            << Helpers::directionName(direction) << ", f=" << floor->getNumber() << "}]";
}

std::set<std::shared_ptr<Floor>, FloorComparator>
StopManager::getStops(std::shared_ptr<Elevator> elevator, Direction direction) const {
  auto it = _stopsPerElevator.find({elevator, direction});
  if (it == _stopsPerElevator.end())
    return std::set<std::shared_ptr<Floor>, FloorComparator>();

  return it->second;
}
