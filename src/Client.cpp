#include "Client.h"
#include "Floor.h"

Client::Client(const int partySize, const int arrivalFloor, const int destination)
    : _partySize(partySize), _destination(destination),
      _arrivalFloor(arrivalFloor) {}

const int Client::getPartySize() const { return _partySize; }

const int Client::getDestination() const { return _destination; }

const int Client::getArrivalFloor() const { return _arrivalFloor; }