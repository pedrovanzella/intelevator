#include "Reporter.h"
#include "Arrival.h"
#include "CostFunctionType.h"
#include "DispatcherType.h"
#include "Scenario.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Trip.h"
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

Reporter::Reporter(std::shared_ptr<Simulator> simulator)
    : _outputPath(simulator->getPath()),
      _scenario(simulator->getScenario()),
      _statistics(simulator->getStatistics()) {}

Reporter::~Reporter() {}

void Reporter::generateReport() {
  std::ofstream f;
  f.open(_outputPath + "report.log");

  print_type_1(f, "Name", _scenario->getName());
  print_type_1(f, "Floors", _scenario->getFloorCount());
  print_type_1(f, "Elevators", _scenario->getElevators());
  print_type_1(f, "Capacity", _scenario->getCapacity());
  print_type_1(f, "Dispatcher", Helpers::dispatcherName(_scenario->getDispatcherType()));
  print_type_1(f, "Cost Function", Helpers::costFunctionName(_scenario->getCostFunctionType()));
  print_type_1(f, "Duration", _scenario->getDuration());
  print_type_1(f, "Seed", _scenario->getSeed());

  f << std::endl;

  print_type_1(f, "Clients arrived", _statistics->getClientsArrived());
  print_type_1(f, "Clients served", _statistics->getClientsServed());

  f << std::endl;

  print_type_2(f, "");
  print_type_2(f, "Average");
  print_type_2(f, "Deviant");
  print_type_2(f, "Total");

  f << std::endl;

  print_type_2(f, "Waiting Time");
  print_type_2(f, _statistics->getAvgWT());
  print_type_2(f, _statistics->getDevWT());
  print_type_2(f, _statistics->getTotalWT());
  f << std::endl;

  print_type_2(f, "Journey Time ");
  print_type_2(f, _statistics->getAvgJT());
  print_type_2(f, _statistics->getDevJT());
  print_type_2(f, _statistics->getTotalJT());

  f << std::endl;
}

void Reporter::generateArrivals() {
  std::ofstream f;
  f.open(_outputPath + "arrivals.log");
  for (auto a : _statistics->getArrivals()) {
    a.printToFile(f);
  }
}

void Reporter::generateDropOffs() {
  std::ofstream f;
  f.open(_outputPath + "trips.log");
  for (auto t : _statistics->getTrips()) {
    t.printToFile(f);
  }
}

void Reporter::generateCharts() {
  // std::string path = getPath();
  // std::string command = "./tools/logparser.py " + path + "/trips.log";
  // system(command.c_str());
}