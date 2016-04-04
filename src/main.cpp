#include <memory>
#include <vector>
#include "easylogging++.h"
#include "Scenario.h"
#include "Simulator.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

int main(int argc, char* argv[])
{
  el::Configurations conf("log.conf");
  el::Loggers::reconfigureLogger("default", conf);
  el::Loggers::reconfigureAllLoggers(conf);
  START_EASYLOGGINGPP(argc, argv);

  auto scenarios = Scenario::Load("config.yaml");
  for (auto scenario : *scenarios)
  {
    Simulator sim(scenario);
    sim.run();
  }

  return 0;
}
