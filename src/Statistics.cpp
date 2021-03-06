#include "Statistics.h"
#include "Arrival.h"
#include "Client.h"
#include "ClientArrival.h"
#include "SchedulerType.h"
#include "CostFunctionType.h"
#include "Elevator.h"
#include "Event.h"
#include "Floor.h"
#include "Scenario.h"
#include "Trip.h"
#include <cmath>
#include <cstdlib>

Statistics::Statistics(std::shared_ptr<const Scenario> scenario)
    : _scenario(scenario), _keepRunning(true), _clientsArrived(0),
      _clientsServed(0) {}

Statistics::~Statistics() {}

std::shared_ptr<const Scenario> Statistics::getScenario() const { return _scenario; }

bool Statistics::keepRunning() const { return _keepRunning; }

void Statistics::notify(const std::shared_ptr<const Event> event) {
  if (event->getType() == EventType::clientArrival) {
    logArrival(std::static_pointer_cast<const ClientArrival>(event));
  }

  if (event->getType() == EventType::finishSimulation) {
    _keepRunning = false;
  }
}

void Statistics::logDropOff(const unsigned long dropOffTime,
                            std::shared_ptr<Elevator> elevator,
                            std::shared_ptr<std::vector<std::shared_ptr<Client>>> droppedPassengers) {
  for (auto passenger : *droppedPassengers) {
    addTrip(dropOffTime, elevator, passenger);
  }
}

void Statistics::addTrip(const unsigned long dropOffTime,
                         const std::shared_ptr<Elevator> elevator,
                         const std::shared_ptr<Client> passenger) {
  auto t = Trip();
  t.elevatorID = elevator->getNumber();
  t.partySize = passenger->getPartySize();
  t.dropOffFloor = elevator->getLocation();
  t.arrivalFloor = passenger->getArrivalFloor();
  t.dropoffTime = dropOffTime;
  t.pickupTime = passenger->getPickupTime();
  t.createTime = passenger->getCreateTime();
  t.clientID = passenger->getId();
  _trips.push_back(t);
  _clientsServed++;
}

void Statistics::logArrival(std::shared_ptr<const ClientArrival> clientArrival) {
  auto a = Arrival();
  a.clientID = clientArrival->getClient()->getId();
  a.arrivalTime = clientArrival->getTime();
  a.arrivalFloor = clientArrival->getClient()->getArrivalFloor();
  a.destinationFloor = clientArrival->getClient()->getDestination();
  a.partySize = clientArrival->getClient()->getPartySize();
  _arrivals.push_back(a);
  _clientsArrived++;
}

int Statistics::getClientsArrived() const {
return _clientsArrived;
}

int Statistics::getClientsServed() const {
  return _clientsServed;
}

double Statistics::getTotalWT() const {
  double total = 0.0;
  for (auto trip : _trips)
    total += trip.pickupTime - trip.createTime;
  return total;
}

double Statistics::getTotalJT() const {
  double total = 0.0;
  for (auto trip : _trips)
    total += trip.dropoffTime - trip.pickupTime;
  return total;
}


double Statistics::getAvgWT() const {
  return getTotalWT() / _clientsServed;
}

double Statistics::getAvgJT() const {
  return getTotalJT() / _clientsServed;
}


double Statistics::getDevWT() const {
  auto awt = getAvgWT();
  double sum = 0.0;
  for (auto trip : _trips) {
    auto wt = trip.pickupTime - trip.createTime;
    sum += pow(wt - awt, 2.0);
  }

  return sqrt(sum / _clientsServed);
}

double Statistics::getDevJT() const {
  auto awt = getAvgWT();
  double sum = 0.0;
  for (auto trip : _trips) {
    auto wt = trip.dropoffTime - trip.pickupTime;
    sum += pow(wt - awt, 2.0);
  }

  return sqrt(sum / _clientsServed);
}

const std::vector<Trip>& Statistics::getTrips() const {
  return _trips;
}

const std::vector<Arrival>& Statistics::getArrivals() const {
  return _arrivals;
}