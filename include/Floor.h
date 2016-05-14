#pragma once

#include "Client.h"
#include "Direction.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "EventQueue.h"
#include <memory>
#include <queue>
#include <set>

class Simulator; // forward declaration

class Floor {
public:
  Floor(const int number, const int population, const float lambda);
  virtual ~Floor();

  int getNumber() const;
  int getLambda() const;
  int getPopulation() const;
  int clientsOnUpLine() const;
  int clientsOnDownLine() const;
  Direction compareTo(const Floor &other) const;

  void setEventFactory(const std::shared_ptr<EventFactory> eventFactory);
  void addClient(const std::shared_ptr<Client> client);
  std::set<int> boardElevator(std::shared_ptr<Elevator> elevator);

  void createFutureArrival(const std::shared_ptr<EventQueue> eventQueue);

  static std::shared_ptr<std::vector<std::shared_ptr<Floor>>> create(const std::shared_ptr<const Simulator> simulator);

private:
  int _number;
  int _population;
  int _lambda;
  std::queue<std::shared_ptr<Client>> _upLine;
  std::queue<std::shared_ptr<Client>> _downLine;
  std::shared_ptr<EventFactory> _eventFactory;
};
