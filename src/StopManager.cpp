#include "StopManager.h"
#include "Direction.h"
#include "Elevator.h"
#include "Floor.h"

std::shared_ptr<Elevator> StopManager::get(std::shared_ptr<Floor> floor,
                                           Direction direction) const {
  if (_stops.find({floor, direction}) == _stops.end())
    return std::shared_ptr<Elevator>(nullptr);

  return _stops.at({floor, direction});
}

void StopManager::set(std::shared_ptr<Floor> floor, Direction direction,
                      std::shared_ptr<Elevator> elevator) {
  if (direction == Direction::None)
    return;

  if (_stops.find({floor, direction}) != _stops.end()) {
    auto old = _stops[{floor, direction}];
    _stopsPerElevator[{old, direction}].erase(floor);
  }

  _stops[{floor, direction}] = elevator;
  _stopsPerElevator[{elevator, direction}].insert(floor);
}

void StopManager::clear(std::shared_ptr<Floor> floor, Direction direction) {
  if (_stops.find({floor, direction}) != _stops.end()) {
    auto elevator = _stops[{floor, direction}];
    _stopsPerElevator[{elevator, direction}].erase(floor);
    _stops.erase({floor, direction});
  }
}

std::set<std::shared_ptr<Floor>>
StopManager::getStops(std::shared_ptr<Elevator> elevator, Direction direction) {
  auto it = _stopsPerElevator.find({elevator, direction});
  if (it == _stopsPerElevator.end())
    return std::set<std::shared_ptr<Floor>>();

  return it->second;
}
