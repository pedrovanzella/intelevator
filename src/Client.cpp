#include "Client.h"
#include "Floor.h"

Client::Client(int partySize, float arrivalTime, const std::shared_ptr<const Floor> destination)
  : _partySize(partySize)
  , _arrivalTime(arrivalTime)
  , _destination(destination)
{
  LOG(DEBUG) << "Created client with partySize=" << _partySize << ", arrivalTime=" << _arrivalTime << " and destination=" << destination->getNumber();
}

int Client::getPartySize() const
{
  return _partySize;
}

float Client::getArrivalTime() const
{
  return _arrivalTime;
}

std::shared_ptr<const Floor> Client::getDestination() const
{
  return _destination;
}
