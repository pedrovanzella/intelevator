#include <memory>
#include <vector>
#include <glog/logging.h>
#include "Scenario.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
  FLAGS_logtostderr = true;
  google::InitGoogleLogging(argv[0]);

  auto scenarios = Scenario::Load("config.yaml");
  for (auto scenario : *scenarios)
  {
    Simulator sim(scenario);
    sim.run();
  }

  return 0;
}
