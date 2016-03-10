#pragma once

#include <map>
#include <queue>
#include <set>
#include "Building.h"
#include "Client.h"
#include "Direction.h"
#include "Floor.h"

class Elevator {
public:
  Elevator(const Building&, Floor&);
  virtual ~Elevator();

  const Building& getBuilding();
  Floor& getLocation();
  Direction getDirection();
  int getOccupation();

private:
  const Building& building;
  Floor& location;
  std::queue<Floor*> destinations;
  std::map<Floor*, std::set<Client*>> passengers;
};