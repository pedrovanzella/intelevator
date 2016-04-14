#pragma once

#include <glog/logging.h>
#include <memory>

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const int arrivalFloor, const int destination, const int id, const long createTime);

  const int getPartySize() const;
  const int getDestination() const;
  const int getArrivalFloor() const;
  const long getCreateTime() const;
  const int getID() const;
  const long getPickupTime() const;


private:
  const int _partySize;
  const int _destination;
  const int _arrivalFloor;
  const long _createTime;
  const int _id;
  long _pickupTime;
};
