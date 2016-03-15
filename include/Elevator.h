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

  void addPassenger(Floor* floor, Client* client);

private:
  std::map<Floor*, std::set<Client*>> _passengers;
  int _maxLoad;
  const Building* _building;
};
