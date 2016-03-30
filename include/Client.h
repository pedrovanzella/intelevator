#pragma once

#include <memory>
#include "easylogging++.h"

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const float arrivalTime, const std::shared_ptr<const Floor> destination);

int getPartySize() const;
float getArrivalTime() const;
std::shared_ptr<const Floor> getDestination() const;

private:
  const int _partySize;
  const float _arrivalTime;
  const std::shared_ptr<const Floor> _destination;
};
