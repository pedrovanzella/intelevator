#pragma once

#include <memory>
#include <glog/logging.h>

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const int arrivalFloor, const int destination);

  const int getPartySize() const;
  const int getDestination() const;
  const int getArrivalFloor() const;

private:
  const int _partySize;
  const int _destination;
  const int _arrivalFloor;
};
