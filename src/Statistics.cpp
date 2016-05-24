#include "Statistics.h"
#include "Arrival.h"
#include "Client.h"
#include "ClientArrival.h"
#include "DispatcherType.h"
#include "CostFunctionType.h"
#include "Elevator.h"
#include "Event.h"
#include "Floor.h"
#include "Scenario.h"
#include "Trip.h"
#include <cmath>
#include <cstdlib>
#include <glog/logging.h>
#include <iomanip>

namespace {
  template<typename T>
  void print_type_1(std::ofstream &os, const std::string& text, const T value) {
    os << std::left << std::setw(16) << std::setfill('.') << text << ": " << value << std::endl;
  }

  template<typename T>
  void print_type_2(std::ofstream &os, const T value) {
    os << std::right << std::setw(13) << std::setfill(' ') << value;
  }
}

Statistics::Statistics(std::shared_ptr<const Scenario> scenario)
    : _scenario(scenario), _keepRunning(true),  _now(std::time(NULL)), _clientsArrived(0),
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
    LOG(INFO) << event->str();
  }
}

void Statistics::logDropOff(const unsigned long dropOffTime,
                            std::shared_ptr<Elevator> elevator,
                            std::shared_ptr<std::vector<std::shared_ptr<Client>>> droppedPassengers) {
  for (auto passenger : *droppedPassengers) {
    LOG(INFO) << "Elevator #" << elevator->getNumber()
              << " dropped client #" << passenger->getId()
              << " at floor #" << elevator->getLocation() << " (t=" << dropOffTime << ").";

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

void Statistics::generateReport() {
  std::string path = getPath();
  LOG(INFO) << "Writing report to '" << path + "/report.log" << "'.";
  std::ofstream f;
  f.open(path + "/report.log");

  print_type_1(f, "Name", _scenario->getName());
  print_type_1(f, "Floors", _scenario->getFloorCount());
  print_type_1(f, "Elevators", _scenario->getElevators());
  print_type_1(f, "Capacity", _scenario->getCapacity());
  print_type_1(f, "Dispatcher", Helpers::dispatcherName(_scenario->getDispatcherType()));
  print_type_1(f, "Cost Function", Helpers::costFunctionName(_scenario->getCostFunctionType()));
  print_type_1(f, "Duration", _scenario->getDuration());
  print_type_1(f, "Seed", _scenario->getSeed());

  f << std::endl;

  print_type_1(f, "Clients arrived", _clientsArrived);
  print_type_1(f, "Clients served", _clientsServed);

  f << std::endl;

  print_type_2(f, "");
  print_type_2(f, "Average");
  print_type_2(f, "Deviant");
  print_type_2(f, "Total");

  f << std::endl;

  print_type_2(f, "Waiting Time");
  print_type_2(f, getAvgWT());
  print_type_2(f, getDevWT());
  print_type_2(f, getTotalWT());
  f << std::endl;

  print_type_2(f, "Journey Time ");
  print_type_2(f, getAvgJT());
  print_type_2(f, getDevJT());
  print_type_2(f, getTotalJT());

  f << std::endl;
}

void Statistics::generateArrivals() {
  std::string path = getPath();
  LOG(INFO) << "Writing trips statistics to '" << path + "/trips.log" << "'.";
  std::ofstream f;
  f.open(path + "/trips.log");
  for (auto t : _trips) {
    t.printToFile(f);
  }
}

void Statistics::generateDropOffs() {
  std::string path = getPath();
  LOG(INFO) << "Writing arrivals statistics to '" << path + "/arrivals.log" << "'.";
  std::ofstream f;
  f.open(path + "/arrivals.log");
  for (auto a : _arrivals) {
    a.printToFile(f);
  }
}

void Statistics::generateCharts() {
  // std::string path = getPath();
  // std::string command = "./tools/logparser.py " + path + "/trips.log";
  // system(command.c_str());
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

std::string Statistics::getPath() const {
  std::tm* ptm = std::localtime(&_now);
  char buffer[32];
  std::strftime(buffer, 32, "%Y%m%d_%H%M%S", ptm);
  auto name = _scenario->getName();

  std::string path = "output/" + name + "_" + buffer;
  std::string command = "mkdir -p " + path;
  system(command.c_str());

  return path;
}