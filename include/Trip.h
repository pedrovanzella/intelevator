#pragma once
#include <fstream>

struct Trip {
  long dropoffTime;
  long pickupTime;
  long createTime;
  int elevatorID;
  int arrivalFloor;
  int dropOffFloor;
  int partySize;
  int clientID;

  Trip();

  void printToFile(std::ofstream &f);
};