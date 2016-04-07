#pragma once

#include <map>
#include <memory>
#include <queue>
#include <set>
#include "Client.h"
#include "Direction.h"
#include "Event.h"
#include "EventObserver.h"

class Elevator : public EventObserver {
public:
  Elevator(int number, int capacity, int floor);
  virtual ~Elevator();

  int getNumber() const;
  int getCapacity() const;
  int getLocation() const;
  int getDestination() const;
  Direction getDirection() const;
  int getAvailableCapacity() const;


  void setDestination(int destination);
  void addPassenger(std::shared_ptr<const Client> client);

  void notify(const std::shared_ptr<const Event> event);

private:
  const int _number;
  const int _capacity;
  int _location;
  int _destination;

  std::set<std::shared_ptr<const Client>> _passengers;
};
