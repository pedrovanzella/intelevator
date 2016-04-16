#pragma once

#include <glog/logging.h>
#include <memory>

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const int arrivalFloor, const int destination, const unsigned long createTime);

  const unsigned long getId() const;
  const int getPartySize() const;
  const int getDestination() const;
  const int getArrivalFloor() const;
  const long getCreateTime() const;
  const long getPickupTime() const;

  void setPickupTime(const unsigned long p);

private:
  static unsigned long nextId;

  const unsigned long _id;
  const int _partySize;
  const int _destination;
  const int _arrivalFloor;
  const long _createTime;
  unsigned long _pickupTime;
};
