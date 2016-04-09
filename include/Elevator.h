#pragma once

#include <map>
#include <memory>
#include <queue>
#include <vector>
#include "Client.h"
#include "Direction.h"
#include "Status.h"
#include "Event.h"
#include "EventObserver.h"

class Elevator : public EventObserver {
public:
  Elevator(int number, int capacity, int floor);
  virtual ~Elevator();

  int getNumber() const;
  int getCapacity() const;
  int getLocation() const;
  int getDestination() const;
  Status getStatus() const;
  Direction getDirection() const;
  int getAvailableCapacity() const;
  int getNextLocation() const;
  const std::shared_ptr<const std::vector<std::shared_ptr<const Client>>> getPassengers() const;

  std::shared_ptr<std::vector<std::shared_ptr<const Client>>> dropPassengersToCurrentLocation();

  void setLocation(int location);
  void setDestination(int destination);
  void setDirection(Direction direction);
  void setStatus(Status status);

  void stopAtNextLocation();
  void addPassenger(std::shared_ptr<const Client> client);
  void notify(const std::shared_ptr<const Event> event);

  void start();
  void stop();
  void turn();

  void move();
private:
  const int _number;
  const int _capacity;
  int _location;
  int _destination;

  Status _status;
  Direction _direction;

  bool _stopAtNextLocation;

  std::shared_ptr<std::vector<std::shared_ptr<const Client>>> _passengers;
};
