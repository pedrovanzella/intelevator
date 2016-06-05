#pragma once

#include <map>
#include <memory>
#include <set>

enum class Direction; // forward declaration
class Elevator;       // forward declaration
class Floor;          // forward declaration

class StopManager {
public:
  bool hasStop(std::shared_ptr<Floor> floor, Direction direction);
  void set(std::shared_ptr<Floor> floor, Direction direction, std::shared_ptr<Elevator> elevator);
  void clear(std::shared_ptr<Floor> floor, std::shared_ptr<Elevator> elevator, Direction direction);
  std::set<std::shared_ptr<Floor>> getStops(std::shared_ptr<Elevator> elevator, Direction direction);

private:
  std::map<std::pair<std::shared_ptr<Elevator>, Direction>, std::set<std::shared_ptr<Floor>>> _stopsPerElevator;
  std::map<std::pair<std::shared_ptr<Floor>, Direction>, std::set<std::shared_ptr<Elevator>>> _stopsPerFloor;
};