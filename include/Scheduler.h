#pragma once

#include <memory>
#include <vector>

class Building;     // forward declaration
class Client;       // forward declaration
class CostFunction; // forward declaration
class Elevator;     // forward declaration

class Scheduler : public std::enable_shared_from_this<Scheduler> {
public:
  Scheduler();
  virtual int schedule(const std::shared_ptr<CostFunction> costFunction,
                       const std::shared_ptr<const Building> building,
                       const std::shared_ptr<const Client> client,
                       const int elevatorToExclude = -1) = 0;

protected:
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>>
  getAvailableElevators(const std::shared_ptr<const Building> building, int elevatorToExclude);

private:
  int _next;
};
