#include "Client.h"
#include "Direction.h"
#include "Floor.h"

unsigned long Client::nextId = 0ul;

Client::Client(const int partySize, const int arrivalFloor,
               const int destination, const unsigned long createTime)
    : _id(++Client::nextId), _partySize(partySize), _destination(destination),
      _arrivalFloor(arrivalFloor), _createTime(createTime), _pickupTime(0) {}

Client::Client(const Client &client)
    : _id(client.getId()), _partySize(client.getPartySize()),
      _destination(client.getDestination()),
      _arrivalFloor(client.getArrivalFloor()),
      _createTime(client.getCreateTime()), _pickupTime(client.getPickupTime()) {
}

void Client::resetIds() {
  Client::nextId = 0ul;
}

const unsigned long Client::getId() const { return _id; }

const int Client::getPartySize() const { return _partySize; }

const int Client::getDestination() const { return _destination; }

const Direction Client::getDirection() const {
  if (_destination > _arrivalFloor)
    return Direction::Up;

  return Direction::Down;
}

const int Client::getArrivalFloor() const { return _arrivalFloor; }

const long Client::getCreateTime() const { return _createTime; }

const long Client::getPickupTime() const { return _pickupTime; }

void Client::setPickupTime(const unsigned long p) { _pickupTime = p; }
