#pragma once

#include <map>
#include <memory>
#include <queue>
#include <set>
#include "Client.h"
#include "Direction.h"

class Elevator {
public:
  Elevator(int number, int capacity, std::shared_ptr<const Floor> floor);
  virtual ~Elevator();

  Direction getDirection() const;
  double getOccupation() const;
  int getNumber() const;
  int getCapacity() const;

  void addPassenger(std::shared_ptr<const Client> client);

  std::shared_ptr<std::set<const Floor>> getDestinations() const;

  std::shared_ptr<const Floor> getCurrentFloor() const;

  constexpr static float seconds_per_floor = 10.f;

private:
  const int _number;
  const int _capacity;
  std::shared_ptr<const Floor> _current_floor;

  std::set<std::shared_ptr<const Client>> _passengers;
};
