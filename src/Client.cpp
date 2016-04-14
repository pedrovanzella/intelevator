#include "Client.h"
#include "Floor.h"

Client::Client(const int partySize, const int arrivalFloor, const int destination, const int id, const long createTime)
    : _partySize(partySize), _destination(destination),
      _arrivalFloor(arrivalFloor), _id(id), _createTime(createTime) {}

const int Client::getPartySize() const { return _partySize; }

const int Client::getDestination() const { return _destination; }

const int Client::getArrivalFloor() const { return _arrivalFloor; }

const long Client::getCreateTime() const { return _createTime; }

const int Client::getID() const { return _id; }

const long Client::getPickupTime() const { return _pickupTime; }

void Client::setPickupTime(long p)
{
  _pickupTime = p;
}
