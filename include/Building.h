#pragma once

#include "EventObserver.h"
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class ClientArrival; // forward declaration
class CostFunction;  // forward declaration
class Dispatcher;    // forward declaration
class Elevator;      // forward declaration
class Floor;         // forward declaration
class Simulator;     // forward declaration
class EventFactory;  // forward declaration

class Building : public EventObserver,
                 public std::enable_shared_from_this<Building> {
public:
  Building(std::shared_ptr<Simulator> simulator,
           std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
           std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
           std::shared_ptr<Dispatcher> dispatcher,
           std::shared_ptr<const CostFunction> costFunction);

  virtual ~Building();

  const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> getElevators() const;
  const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> getFloors() const;

  const std::shared_ptr<Floor> getFloor(int number) const;
  const std::shared_ptr<Elevator> getElevator(int number) const;

  void notify(const std::shared_ptr<const Event> event);
  void createFutureArrival();

  std::string stopsToString() const;

private:
  std::shared_ptr<Simulator> _simulator;
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> _floors;
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> _elevators;
  const std::shared_ptr<Dispatcher> _dispatcher;
  const std::shared_ptr<const CostFunction> _costFunction;
  std::map<std::shared_ptr<Elevator>, std::set<int>> _stops;
  int _lastEventTime;

  void doClientArrival(std::shared_ptr<const ClientArrival> event);
  void updateElevators(const unsigned long time);
  void assignDestinationForElevator(const std::shared_ptr<Elevator> elevator);
  bool mustStopAtNextLocation(const std::shared_ptr<Elevator> elevator);
  void registerNewStops(const std::shared_ptr<Elevator> elevator, const std::set<int> stops);
};
