#pragma once

#include <memory>
#include <glog/logging.h>

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const float arrivalTime, int destination);

int getPartySize() const;
float getArrivalTime() const;
int getDestination() const;

private:
  const int _partySize;
  const float _arrivalTime;
  const int _destination;
};
