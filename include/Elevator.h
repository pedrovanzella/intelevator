#pragma once

#include <map>
#include <memory>
#include <queue>
#include <vector>

class Client;         // forward declaration
enum class Direction; // forward declaration
class Event;          // forward declaration
class Scenario;       // forward declaration
class Simulator;      // forward declaration
enum class Status;    // forward declaration

class Elevator: public std::enable_shared_from_this<Elevator> {
public:
  Elevator(int number, int capacity, int floor);
  Elevator(const Elevator &elevator);
  virtual ~Elevator();

  int getNumber() const;
  int getCapacity() const;
  int getLocation() const;
  float getOccupation() const;
  std::pair<int, Direction> getDestination() const;
  Status getStatus() const;
  Direction getDirection() const;
  const std::shared_ptr<const std::vector<std::shared_ptr<Client>>> getPassengers() const;

  void setDestination(std::pair<int, Direction> destination);

  bool canEnter(std::shared_ptr<const Client> client) const;
  void addPassenger(std::shared_ptr<Client> client);
  void move();
  std::shared_ptr<std::vector<std::shared_ptr<Client>>> dropPassengersToCurrentLocation();

  static std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> create(const std::shared_ptr<const Simulator> simulator);

private:
  const int _number;
  const int _capacity;
  int _location;
  std::pair<int, Direction> _destination;
  Status _status;
  Direction _direction;
  std::shared_ptr<std::vector<std::shared_ptr<Client>>> _passengers;
};
