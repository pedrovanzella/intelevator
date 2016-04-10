#include "Client.h"
#include "Floor.h"

Client::Client(const int partySize, const float arrivalTime, const int arrivalFloor, const int destination)
  : _partySize(partySize)
  , _arrivalTime(arrivalTime)
  , _destination(destination)
  , _arrivalFloor(arrivalFloor)
{}

const int Client::getPartySize() const
{
  return _partySize;
}

const float Client::getArrivalTime() const
{
  return _arrivalTime;
}

const int Client::getDestination() const
{
  return _destination;
}

const int Client::getArrivalFloor() const
{
  return _arrivalFloor;
}