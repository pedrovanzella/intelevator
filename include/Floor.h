#pragma once

#include <memory>
#include <queue>
#include <set>
#include "Client.h"
#include "Elevator.h"
#include "EventObserver.h"
#include "Direction.h"

class Floor
{
public:
  Floor(int number, int population);
  virtual ~Floor();

  int getNumber() const;
  int getPopulation() const;
  Direction compareTo(const Floor& other) const;

  void addClient(const std::shared_ptr<const Client> client);
  std::set<int> boardElevator(std::shared_ptr<Elevator> elevator);

private:
  int _number;
  int _population;
  std::queue<std::shared_ptr<const Client>> _upLine;
  std::queue<std::shared_ptr<const Client>> _downLine;
};
