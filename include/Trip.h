#pragma once

#include <memory>

class Trip {
public:
  long dropoffTime;
  long pickupTime;
  long createTime;
  int elevatorID;
  int arrivalFloor;
  int dropOffFloor;
  int partySize;
  int clientID;

  Trip();
};