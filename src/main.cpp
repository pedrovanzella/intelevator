#include "Scenario.h"
#include "Simulator.h"
#include <glog/logging.h>
#include <memory>

using namespace std;

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  auto scenarios = Scenario::Load("config.yaml");
  for (auto scenario : *scenarios) {
    auto simulator = std::make_shared<Simulator>(scenario);
    simulator->run();
  }

  return 0;
}
