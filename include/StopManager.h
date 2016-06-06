#pragma once

#include <map>
#include <memory>
#include <set>
#include "Floor.h"

enum class Direction;  // forward declaration
class Elevator;        // forward declaration

struct FloorComparator {
  bool operator()(const std::shared_ptr<Floor> &lhs,
                  const std::shared_ptr<Floor> &rhs) const {
    return lhs->getNumber() < rhs->getNumber();
  }
};

class StopManager {
public:
  bool hasStop(std::shared_ptr<Floor> floor, Direction direction);
  void set(std::shared_ptr<Floor> floor, Direction direction, std::shared_ptr<Elevator> elevator);
  void clear(std::shared_ptr<Floor> floor, std::shared_ptr<Elevator> elevator, Direction direction);
  std::set<std::shared_ptr<Floor>, FloorComparator> getStops(std::shared_ptr<Elevator> elevator, Direction direction);

private:
  std::map<std::pair<std::shared_ptr<Elevator>, Direction>, std::set<std::shared_ptr<Floor>, FloorComparator>> _stopsPerElevator;
  std::map<std::pair<std::shared_ptr<Floor>, Direction>, std::set<std::shared_ptr<Elevator>>> _stopsPerFloor;
};