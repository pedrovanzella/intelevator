#include "Scenario.h"
#include "Simulator.h"
#include "Reporter.h"
#include <glog/logging.h>
#include <memory>

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  auto scenarios = Scenario::Load("config.yaml");
  auto reporter = std::make_shared<Reporter>();

  for (auto scenario : *scenarios) {
    auto simulator = std::make_shared<Simulator>(scenario);
    simulator->run();
    reporter->generate(simulator->getStatistics());
  }

  reporter->generate();

  return 0;
}
