#include "Reporter.h"
#include "Arrival.h"
#include "CostFunctionType.h"
#include "SchedulerType.h"
#include "Scenario.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Trip.h"
#include <iomanip>
#include <iostream>

namespace {
  template<typename T>
  void print(std::ofstream &os, const std::string& text, const T value) {
    os << std::left << std::setw(16) << std::setfill('.') << text << ": " << value << std::endl;
  }

  template<typename T>
  void print(std::ofstream &os, const T value) {
    os << std::right << std::setw(13) << std::setfill(' ') << value;
  }
}

Reporter::Reporter() {}

Reporter::~Reporter() {}

void Reporter::add(std::shared_ptr<Statistics> statistics) {
  auto group = statistics->getScenario()->getGroup();
  _stats[group].push_back(statistics);
}

void Reporter::generate() {
  for (auto const &it : _stats) {
    for (auto const &statistics : it.second) {
      auto path = statistics->getScenario()->getPath();
      auto scenarioPath = path + statistics->getScenario()->getName() + "/";
      generateArrivals(scenarioPath, statistics);
      generateDropOffs(scenarioPath, statistics);
    }
  }
}

void Reporter::generateReport() {
  // std::ofstream f;
  // f.open(_outputPath + "report.log");

  // print(f, "Name", _scenario->getName());
  // print(f, "Duration", _scenario->getDuration());
  // print(f, "Scheduler", Helpers::schedulerName(_scenario->getSchedulerType()));
  // print(f, "Cost Function", Helpers::costFunctionName(_scenario->getCostFunctionType()));
  // print(f, "Seed", _scenario->getSeed());
  // print(f, "Elevators", _scenario->getElevators());
  // print(f, "Capacity", _scenario->getCapacity());
  // print(f, "Floors", _scenario->getFloorCount());

  // f << std::endl;

  // print(f, "Clients arrived", _statistics->getClientsArrived());
  // print(f, "Clients served", _statistics->getClientsServed());

  // f << std::endl;

  // print(f, "");
  // print(f, "Average");
  // print(f, "Deviant");
  // print(f, "Total");

  // f << std::endl;

  // print(f, "Waiting Time");
  // print(f, _statistics->getAvgWT());
  // print(f, _statistics->getDevWT());
  // print(f, _statistics->getTotalWT());
  // f << std::endl;

  // print(f, "Journey Time ");
  // print(f, _statistics->getAvgJT());
  // print(f, _statistics->getDevJT());
  // print(f, _statistics->getTotalJT());

  // f << std::endl;
}

void Reporter::generateArrivals(const std::string path, std::shared_ptr<Statistics> statistics) {
  std::ofstream f;
  f.open(path + "arrivals.log");
  for (auto a : statistics->getArrivals()) {
    a.printToFile(f);
  }
}

void Reporter::generateDropOffs(const std::string path, std::shared_ptr<Statistics> statistics) {
  std::ofstream f;
  f.open(path + "trips.log");
  for (auto t : statistics->getTrips()) {
    t.printToFile(f);
  }
}

void Reporter::generateCharts() {
  // std::string path = getPath();
  // std::string command = "./tools/logparser.py " + path + "/trips.log";
  // system(command.c_str());
}