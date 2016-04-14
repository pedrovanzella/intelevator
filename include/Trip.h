#pragma once

#include <memory>

class Trip {
public:
  long waitingTime;
  long journeyTime;
  long arrivalTime;
  int elevatorID;
  int arrivalFloor;
  int dropOffFloor;
  int partySize;
  int clientID;

  Trip();
};