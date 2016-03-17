#pragma once

#include <map>
#include <queue>
#include <set>
#include "Building.h"
#include "Client.h"
#include "Config.h"
#include "Direction.h"

class Elevator {
public:
  Elevator(const Config& config, const Building* building);
  virtual ~Elevator();

  Direction getDirection() const;
  double getOccupation() const;

  void addPassenger(Client& client);

  std::shared_ptr<std::set<Floor const&>> getDestinations() const;

private:
  std::set<Client&> _passengers;
  int _maxLoad;
  const Building* _building;
};
