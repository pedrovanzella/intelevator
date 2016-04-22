#include "Trip.h"

Trip::Trip() {}

void Trip::printToFile(std::ofstream &f)
{
  f   << clientID << " "
      << partySize << " "
      << elevatorID << " "
      << arrivalFloor << " "
      << dropOffFloor << " "
      << createTime << " "
      << pickupTime << " "
      << dropoffTime << "\n";
}