#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>
#include "CostFunction.h"
#include "Dispatcher.h"
#include "EventObserver.h"

class Elevator; // forward declaration
class Floor;    // forward declaration

class Building : public EventObserver, public std::enable_shared_from_this<Building>
{
public:
  Building(std::shared_ptr<std::vector<std::shared_ptr<const Floor>>> floors,
           std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
           std::shared_ptr<const Dispatcher> dispatcher,
           std::shared_ptr<const CostFunction> costFunction);

  virtual ~Building();

  void setLocation(std::shared_ptr<const Elevator> elevator, std::shared_ptr<const Floor> location);
  const std::shared_ptr<const Floor> getLocation(std::shared_ptr<const Elevator> elevator);
  const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> getElevators() const;
  const std::shared_ptr<std::vector<std::shared_ptr<const Floor>>> getFloors() const;

  const std::shared_ptr<const Floor> getFloor(int number) const;
  const std::shared_ptr<const Elevator> getElevator(int number) const;

  void notify(const std::shared_ptr<const Event> event);

private:
  std::shared_ptr<std::vector<std::shared_ptr<const Floor>>> _floors;
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> _elevators;
  const std::shared_ptr<const Dispatcher> _dispatcher;
  const std::shared_ptr<const CostFunction> _costFunction;

  std::map<std::shared_ptr<const Elevator>, std::shared_ptr<const Floor>> _locations;
};
