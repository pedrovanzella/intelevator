#include "Client.h"
#include "Floor.h"

Client::Client(int partySize, float arrivalTime, int destination)
  : _partySize(partySize)
  , _arrivalTime(arrivalTime)
  , _destination(destination)
{}

int Client::getPartySize() const
{
  return _partySize;
}

float Client::getArrivalTime() const
{
  return _arrivalTime;
}

int Client::getDestination() const
{
  return _destination;
}
