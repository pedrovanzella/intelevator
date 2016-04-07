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
  void setDestination(int destination);

  Direction getDirection() const;
  int getAvailableCapacity() const;

  void addPassenger(std::shared_ptr<const Client> client);

  constexpr static float seconds_per_floor = 10.f;

  void notify(const std::shared_ptr<const Event> event) const;

private:
  const int _number;
  const int _capacity;
  int _location;
  int _destination;

  std::set<std::shared_ptr<const Client>> _passengers;
};
