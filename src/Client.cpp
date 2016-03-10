#include "Client.h"

Client::Client(int partySize, float arrivalTime, const Floor& destination)
  : partySize(partySize)
  , arrivalTime(arrivalTime)
  , destination(destination)
{}