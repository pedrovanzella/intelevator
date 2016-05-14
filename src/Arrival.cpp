#include "Arrival.h"

Arrival::Arrival() {}

void Arrival::printToFile(std::ofstream &f) {
  f << arrivalFloor << " "
    << arrivalTime << " "
    << partySize << " "
    << destinationFloor << " "
    << clientID << "\n";
}