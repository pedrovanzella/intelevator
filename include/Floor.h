#pragma once

#include "Client.h"
#include "Direction.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "Scenario.h"
#include <memory>
#include <queue>
#include <set>

class Floor {
public:
  Floor(const int number, const int population, const std::string seed = "");
  virtual ~Floor();

  int getNumber() const;
  int getPopulation() const;
  Direction compareTo(const Floor &other) const;

  void addClient(const std::shared_ptr<Client> client);
  std::set<int> boardElevator(std::shared_ptr<Elevator> elevator);

  static std::shared_ptr<std::vector<std::shared_ptr<Floor>>> createFloors(const std::shared_ptr<const Scenario> scenario);

private:
  int _number;
  int _population;
  std::queue<std::shared_ptr<Client>> _upLine;
  std::queue<std::shared_ptr<Client>> _downLine;
  std::unique_ptr<EventFactory> _eventFactory;
};
