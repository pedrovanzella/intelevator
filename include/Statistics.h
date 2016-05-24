#pragma once

#include "EventObserver.h"
#include <ctime>
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
class Scenario;      // forward declaration
struct Trip;         // forward declaration

class Statistics : public EventObserver {
public:
  Statistics(std::shared_ptr<const Scenario> scenario);
  virtual ~Statistics();

  bool keepRunning() const;
  std::shared_ptr<const Scenario> getScenario() const;
  std::string getPath() const;

  int getClientsArrived() const;
  int getClientsServed() const;

  double getTotalWT() const;
  double getTotalJT() const;

  double getAvgWT() const;
  double getAvgJT() const;

  double getDevWT() const;
  double getDevJT() const;

  void notify(const std::shared_ptr<const Event> event);

  void logDropOff(const unsigned long dropOffTime,
                  std::shared_ptr<Elevator> elevator,
                  std::shared_ptr<std::vector<std::shared_ptr<Client>>> droppedPassengers);

  void addTrip(const unsigned long dropOffTime,
               const std::shared_ptr<Elevator> elevator,
               const std::shared_ptr<Client> passenger);

  void logArrival(std::shared_ptr<const ClientArrival> clientArrival);

  void generateReport();
  void generateArrivals();
  void generateDropOffs();
  void generateCharts();

private:
  std::shared_ptr<const Scenario> _scenario;
  bool _keepRunning;
  std::vector<Trip> _trips;
  std::vector<Arrival> _arrivals;
  std::time_t _now;

  int _clientsArrived;
  int _clientsServed;
};
