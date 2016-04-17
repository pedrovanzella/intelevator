#pragma once

#include <memory>
#include <queue>
#include <set>
#include "Client.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "Direction.h"
#include "Scenario.h"

class Floor
{
public:
  Floor(int number, int population);
  virtual ~Floor();

  int getNumber() const;
  int getPopulation() const;
  Direction compareTo(const Floor& other) const;

  void addClient(const std::shared_ptr<Client> client);
  std::set<int> boardElevator(std::shared_ptr<Elevator> elevator);

  static std::shared_ptr<std::vector<std::shared_ptr<Floor>>> createFloors(std::shared_ptr<Scenario> scenario);

private:
  int _number;
  int _population;
  std::queue<std::shared_ptr<Client>> _upLine;
  std::queue<std::shared_ptr<Client>> _downLine;

  std::unique_ptr<EventFactory> _eventFactory;
};
