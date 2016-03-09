#include "Client.h"

Client::Client(int partySize, float arrivalTime, const Floor& destination)
  : partySize(partySize)
  , arrivalTime(arrivalTime)
  , destination(destination)
{}

const int Client::getPartySize()
{
  return this->partySize;
}

const float Client::getArrivalTime()
{
  return this->arrivalTime;
}

const Floor& Client::getDestination()
{
  return this->destination;
}
