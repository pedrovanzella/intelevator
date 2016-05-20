#pragma once

#include "EventObserver.h"
#include <fstream>
#include <list>
#include <memory>
#include <string>
#include <vector>

struct Arrival;      // forward declaration
class Client;        // forward declaration
class ClientArrival; // forward declaration
class Elevator;      // forward declaration
class Event;         // forward declaration
class Floor;         // forward declaration
struct Trip;         // forward declaration

class Statistics : public EventObserver {
public:
  Statistics();
  virtual ~Statistics();

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event);

  void logDropOff(const unsigned long dropOffTime,
                  std::shared_ptr<Elevator> elevator,
                  std::shared_ptr<std::vector<std::shared_ptr<Client>>> droppedPassengers);

  void addTrip(const unsigned long dropOffTime,
               const std::shared_ptr<Elevator> elevator,
               const std::shared_ptr<Client> passenger);

  void logArrival(std::shared_ptr<const ClientArrival> clientArrival);

  void printToFile(std::string name);

private:
  bool _keepRunning;
  std::vector<Trip> _trips;
  std::vector<Arrival> _arrivals;

  int _clientsArrived;
  int _clientsServed;
};
