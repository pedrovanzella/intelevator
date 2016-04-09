#pragma once

#include "CostFunction.h"
#include "Dispatcher.h"
#include "EventObserver.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building : public EventObserver,
                 public std::enable_shared_from_this<Building> {
public:
  Building(std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
           std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
           std::shared_ptr<const Dispatcher> dispatcher,
           std::shared_ptr<const CostFunction> costFunction);

  virtual ~Building();

  const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> getElevators() const;
  const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> getFloors() const;

  const std::shared_ptr<Floor> getFloor(int number) const;
  const std::shared_ptr<Elevator> getElevator(int number) const;

  void notify(const std::shared_ptr<const Event> event);

  std::string stopsToString() const;

private:
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> _floors;
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> _elevators;
  const std::shared_ptr<const Dispatcher> _dispatcher;
  const std::shared_ptr<const CostFunction> _costFunction;

  std::map<int, std::vector<bool>> _stops;
};
