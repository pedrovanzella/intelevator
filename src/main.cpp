#include "Scenario.h"
#include "Simulator.h"
#include "Reporter.h"
#include <glog/logging.h>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  auto scenarios = Scenario::Load("config.yaml");
  for (auto scenario : *scenarios) {
    auto simulator = std::make_shared<Simulator>(scenario);
    simulator->run();

    auto reporter = std::make_shared<Reporter>(simulator);
    reporter->generateReport();
    reporter->generateArrivals();
    reporter->generateDropOffs();
    reporter->generateCharts();
  }

  return 0;
}
