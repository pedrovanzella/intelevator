#include "Client.h"

Client::Client(int partySize, float arrivalTime, const std::shared_ptr<const Floor> destination)
  : _partySize(partySize)
  , _arrivalTime(arrivalTime)
  , _destination(destination)
{}

const int Client::getPartySize()
{
  return _partySize;
}

const float Client::getArrivalTime()
{
  return _arrivalTime;
}

const std::shared_ptr<const Floor> Client::getDestination()
{
  return _destination;
}
