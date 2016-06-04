#include "Reporter.h"
#include "Arrival.h"
#include "Clock.h"
#include "CostFunctionType.h"
#include "SchedulerType.h"
#include "Scenario.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Trip.h"
#include <iomanip>
#include <sstream>
#include <iostream>

namespace {
  template<typename T>
  void print(std::ostream &os, const std::string& text, const T value) {
    os << std::left << std::setw(16) << std::setfill('.') << text << ": " << value << std::endl;
  }

  template<typename T>
  void printr(std::ostream &os, const T value) {
    os << std::right << std::setw(16) << std::setfill(' ') << value;
  }

  void printr(std::ostream &os, const double value) {
    os << std::right << std::setw(16) << std::setfill(' ') << std::setprecision(4) << std::fixed << value;
  }

  template<typename T>
  void printl(std::ostream &os, const T value) {
    os << std::left << std::setw(32) << std::setfill(' ') << value;
  }
}

Reporter::Reporter() {}

Reporter::~Reporter() {}

void Reporter::generate(std::shared_ptr<Simulator> simulator) {
  auto name = simulator->getScenario()->getName();
  _simulators[name].push_back(simulator);
}

void Reporter::generate() {
  std::cout << "Generating reports... ";
  std::cout.flush();

  for (auto const &it : _simulators) {
    generateUnifiedReport(it.second);

    for (auto const &simulator : it.second) {
      generateReport(simulator);
      generateArrivals(simulator);
      generateDropOffs(simulator);
      generateCharts(simulator);
    }
  }

  std::cout << "done!\n";
  std::cout.flush();
}

void Reporter::generateUnifiedReport(std::vector<std::shared_ptr<Simulator>> simulators) {
  auto scenario = simulators[0]->getScenario();

  std::stringstream header;
  std::stringstream waitingTime;
  std::stringstream journeyTime;
  std::stringstream clients;

  for (auto it = simulators.begin(); it != simulators.end(); ++it) {
    auto simulator = *it;
    auto statistics = simulator->getStatistics();
    auto scenario = simulator->getScenario();
    auto clock = simulator->getClock();

    if (it == simulators.begin()) {
      print(header, "Name", scenario->getName());
      print(header, "Duration", scenario->getDuration());
      print(header, "Seed", scenario->getSeed());
      print(header, "Elevators", scenario->getElevatorCount());
      print(header, "Capacity", scenario->getCapacity());
      print(header, "Floors", scenario->getFloorCount());
      print(header, "Horizon", scenario->getPlanningHorizon());

      waitingTime << "WAITING TIME" << std::endl;
      printl(waitingTime, "");
      printr(waitingTime, "Average");
      printr(waitingTime, "Deviant");
      printr(waitingTime, "Total");
      waitingTime << std::endl;

      journeyTime << "JOURNEY TIME" << std::endl;
      printl(journeyTime, "");
      printr(journeyTime, "Average");
      printr(journeyTime, "Deviant");
      printr(journeyTime, "Total");
      journeyTime << std::endl;

      clients << "CLIENTS" << std::endl;
      printl(clients, "");
      printr(clients, "Arrived");
      printr(clients, "Served");
      printr(clients, "Duration");
      clients << std::endl;
    }

    auto scheduler = Helpers::schedulerName(scenario->getSchedulerType());
    auto costFunction = Helpers::costFunctionName(scenario->getCostFunctionType());

    printl(waitingTime, scheduler + "/" + costFunction);
    printr(waitingTime, statistics->getAvgWT());
    printr(waitingTime, statistics->getDevWT());
    printr(waitingTime, statistics->getTotalWT());
    waitingTime << std::endl;

    printl(journeyTime, scheduler + "/" + costFunction);
    printr(journeyTime, statistics->getAvgJT());
    printr(journeyTime, statistics->getDevJT());
    printr(journeyTime, statistics->getTotalJT());
    journeyTime << std::endl;

    printl(clients, scheduler + "/" + costFunction);
    printr(clients, statistics->getClientsArrived());
    printr(clients, statistics->getClientsServed());
    printr(clients, clock->currentTime());
    clients << std::endl;
  }

  std::ofstream f;
  f.open(scenario->getBasePath() + "report.log");
  f << header.rdbuf() << std::endl
    << waitingTime.rdbuf() << std::endl
    << journeyTime.rdbuf() << std::endl
    << clients.rdbuf() << std::endl;
}

void Reporter::generateReport(std::shared_ptr<Simulator> simulator) {
  auto statistics = simulator->getStatistics();
  auto scenario = simulator->getScenario();
  auto clock = simulator->getClock();

  std::ofstream f;
  f.open(scenario->getPath() + "report.log");

  print(f, "Name", scenario->getName());
  print(f, "Duration", scenario->getDuration());
  print(f, "Scheduler", Helpers::schedulerName(scenario->getSchedulerType()));
  print(f, "Cost Function", Helpers::costFunctionName(scenario->getCostFunctionType()));
  print(f, "Seed", scenario->getSeed());
  print(f, "Elevators", scenario->getElevatorCount());
  print(f, "Capacity", scenario->getCapacity());
  print(f, "Floors", scenario->getFloorCount());
  print(f, "Horizon", scenario->getPlanningHorizon());

  f << std::endl;

  print(f, "Clients arrived", statistics->getClientsArrived());
  print(f, "Clients served", statistics->getClientsServed());
  print(f, "Duration", clock->currentTime());

  f << std::endl;

  printl(f, "");
  printr(f, "Average");
  printr(f, "Deviant");
  printr(f, "Total");

  f << std::endl;

  printl(f, "Waiting Time");
  printr(f, statistics->getAvgWT());
  printr(f, statistics->getDevWT());
  printr(f, statistics->getTotalWT());
  f << std::endl;

  printl(f, "Journey Time ");
  printr(f, statistics->getAvgJT());
  printr(f, statistics->getDevJT());
  printr(f, statistics->getTotalJT());

  f << std::endl;
}

void Reporter::generateArrivals(std::shared_ptr<Simulator> simulator) {
  auto statistics = simulator->getStatistics();
  auto scenario = statistics->getScenario();

  std::ofstream f;
  f.open(scenario->getPath() + "arrivals.log");
  f << "arrivalFloor arrivalTime partySize destinationFloor clientID\n";
  for (auto a : statistics->getArrivals()) {
    a.printToFile(f);
  }
}

void Reporter::generateDropOffs(std::shared_ptr<Simulator> simulator) {
  auto statistics = simulator->getStatistics();
  auto scenario = statistics->getScenario();

  std::ofstream f;
  f.open(scenario->getPath() + "trips.log");
  f << "clientID partySize elevatorID arrivalFloor dropoffFloor createTime pickupTime dropoffTime\n";
  for (auto t : statistics->getTrips()) {
    t.printToFile(f);
  }
}

void Reporter::generateCharts(std::shared_ptr<Simulator> simulator) {
  auto statistics = simulator->getStatistics();
  // auto scenario = statistics->getScenario();
  // std::string command = "./tools/logparser.py " + scenario->getPath() + "trips.log";
  // system(command.c_str());
}
