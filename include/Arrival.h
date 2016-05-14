#pragma once

#include <fstream>

struct Arrival {
  int clientID;
  int arrivalTime;
  int arrivalFloor;
  int destinationFloor;
  int partySize;

  Arrival();

  void printToFile(std::ofstream &f);
};