#pragma once

#include <memory>
#include <glog/logging.h>

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const float arrivalTime, const int arrivalFloor, const int destination);

  const int getPartySize() const;
  const float getArrivalTime() const;
  const int getDestination() const;
  const int getArrivalFloor() const;

private:
  const int _partySize;
  const float _arrivalTime;
  const int _destination;
  const int _arrivalFloor;
};
