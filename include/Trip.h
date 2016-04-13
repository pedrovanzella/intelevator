#pragma once

#include <memory>

class Trip {
public:
  float waitingTime;
  float journeyTime;
  float arrivalTime;
  int arrivalFloor;
  int dropOffFloor;
  int partySize;
  int clientID;

  Trip();
};