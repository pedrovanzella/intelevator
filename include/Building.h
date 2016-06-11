#pragma once

#include "EventObserver.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class ClientArrival;  // forward declaration
class Clock;          // forward declaration
class CostFunction;   // forward declaration
enum class Direction; // forward declaration
class Scheduler;      // forward declaration
class Elevator;       // forward declaration
class EventFactory;   // forward declaration
class Floor;          // forward declaration
class Simulator;      // forward declaration
class StopManager;    // forward declaration

class Building : public EventObserver,
                 public std::enable_shared_from_this<Building> {
public:
  Building(std::shared_ptr<const Simulator> simulator,
           std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
           std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
           std::shared_ptr<Scheduler> scheduler,
           std::shared_ptr<CostFunction> costFunction);

  Building(const Building& building, std::shared_ptr<const Simulator> simulator);

  virtual ~Building();

  const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> getElevators() const;
  const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> getFloors() const;
  const std::shared_ptr<Floor> getFloor(int number) const;
  const std::shared_ptr<Elevator> getElevator(int number) const;
  const std::shared_ptr<const Simulator> getSimulator() const;
  const std::shared_ptr<StopManager> getStopManager() const;

  void step();
  void notify(const std::shared_ptr<const Event> event);
  void initializeArrivals();

  void setStop(const int destination, Direction direction, std::shared_ptr<Elevator> elevator);
  bool mustStop(const int destination, Direction direction, std::shared_ptr<Elevator> elevator);

private:
  std::shared_ptr<const Simulator> _simulator;
  std::shared_ptr<Clock> _clock;
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> _floors;
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> _elevators;
  const std::shared_ptr<Scheduler> _scheduler;
  const std::shared_ptr<CostFunction> _costFunction;
  const std::shared_ptr<StopManager> _stopManager;

  void doClientArrival(std::shared_ptr<const ClientArrival> event);
  void updateElevator(const std::shared_ptr<Elevator> elevator);
  std::pair<int, Direction> getDestinationForElevator(const std::shared_ptr<Elevator> elevator);
  bool mustStop(const std::shared_ptr<Elevator> elevator);
  void stop(const std::shared_ptr<Elevator> elevator);
  void registerNewStops(std::shared_ptr<Elevator> elevator, std::set<int> newStops);
};
