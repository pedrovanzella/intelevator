#include "Client.h"

Client::Client(int partySize, float arrivalTime, const Floor& destination)
  : _partySize(partySize)
  , _arrivalTime(arrivalTime)
  , _destination(destination)
{}