#pragma once

#include <map>
#include <memory>
#include <queue>
#include <set>
#include "Building.h"
#include "Client.h"
#include "Direction.h"

class Elevator {
public:
  Elevator(const std::shared_ptr<const Building> building, int number);
  virtual ~Elevator();

  Direction getDirection() const;
  double getOccupation() const;
  int getNumber() const;

  void addPassenger(std::shared_ptr<const Client> client);

  std::shared_ptr<std::set<const Floor>> getDestinations() const;

  std::shared_ptr<const Floor> getCurrentFloor() const;

  constexpr static float seconds_per_floor = 10.f;

private:
  const std::shared_ptr<const Building> _building;
  int _number;
  std::set<std::shared_ptr<const Client>> _passengers;
  std::shared_ptr<const Floor> _current_floor;
};
