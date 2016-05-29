#include "Reporter.h"
#include "Arrival.h"
#include "CostFunctionType.h"
#include "SchedulerType.h"
#include "Scenario.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Trip.h"
#include <iomanip>
#include <sstream>

namespace {
  template<typename T>
  void print(std::ostream &os, const std::string& text, const T value) {
    os << std::left << std::setw(16) << std::setfill('.') << text << ": " << value << std::endl;
  }

  template<typename T>
  void printr(std::ostream &os, const T value) {
    os << std::right << std::setw(16) << std::setfill(' ') << value;
  }

  template<typename T>
  void printl(std::ostream &os, const T value) {
    os << std::left << std::setw(32) << std::setfill(' ') << value;
  }
}

Reporter::Reporter() {}

Reporter::~Reporter() {}

void Reporter::add(std::shared_ptr<Statistics> statistics) {
  auto name = statistics->getScenario()->getName();
  _stats[name].push_back(statistics);
}

void Reporter::generate() {
  for (auto const &it : _stats) {
    generateUnifiedReport(it.second);

    for (auto const &statistics : it.second) {
      generateReport(statistics);
      generateArrivals(statistics);
      generateDropOffs(statistics);
    }
  }
}

void Reporter::generateUnifiedReport(std::vector<std::shared_ptr<Statistics>> stats) {
  auto scenario = stats[0]->getScenario();

  std::stringstream header;
  std::stringstream waitingTime;
  std::stringstream journeyTime;
  std::stringstream clients;

  for (auto it = stats.begin(); it != stats.end(); ++it) {
    auto statistics = *it;
    auto scenario = statistics->getScenario();

    if (it == stats.begin()) {
      print(header, "Name", scenario->getName());
      print(header, "Duration", scenario->getDuration());
      print(header, "Seed", scenario->getSeed());
      print(header, "Elevators", scenario->getElevators());
      print(header, "Capacity", scenario->getCapacity());
      print(header, "Floors", scenario->getFloorCount());

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
    clients << std::endl;
  }

  std::ofstream f;
  f.open(scenario->getBasePath() + "report.log");
  f << header.rdbuf() << std::endl
    << waitingTime.rdbuf() << std::endl
    << journeyTime.rdbuf() << std::endl
    << clients.rdbuf() << std::endl;
}

void Reporter::generateReport(std::shared_ptr<Statistics> statistics) {
  auto scenario = statistics->getScenario();
  std::ofstream f;
  f.open(scenario->getPath() + "report.log");

  print(f, "Name", scenario->getName());
  print(f, "Duration", scenario->getDuration());
  print(f, "Scheduler", Helpers::schedulerName(scenario->getSchedulerType()));
  print(f, "Cost Function", Helpers::costFunctionName(scenario->getCostFunctionType()));
  print(f, "Seed", scenario->getSeed());
  print(f, "Elevators", scenario->getElevators());
  print(f, "Capacity", scenario->getCapacity());
  print(f, "Floors", scenario->getFloorCount());

  f << std::endl;

  print(f, "Clients arrived", statistics->getClientsArrived());
  print(f, "Clients served", statistics->getClientsServed());

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

void Reporter::generateArrivals(std::shared_ptr<Statistics> statistics) {
  auto scenario = statistics->getScenario();
  std::ofstream f;
  f.open(scenario->getPath() + "arrivals.log");
  f << "arrivalFloor arrivalTime partySize destinationFloor clientID\n";
  for (auto a : statistics->getArrivals()) {
    a.printToFile(f);
  }
}

void Reporter::generateDropOffs(std::shared_ptr<Statistics> statistics) {
  auto scenario = statistics->getScenario();
  std::ofstream f;
  f.open(scenario->getPath() + "trips.log");
  f << "clientID partySize elevatorID arrivalFloor dropoffFloor createTime pickupTime dropoffTime\n";
  for (auto t : statistics->getTrips()) {
    t.printToFile(f);
  }
}

void Reporter::generateCharts() {
  // std::string path = getPath();
  // std::string command = "./tools/logparser.py " + path + "/trips.log";
  // system(command.c_str());
}
