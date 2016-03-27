#include <memory>
#include "easylogging++.h"
#include "Simulator.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

int main(int argc, char* argv[])
{
  START_EASYLOGGINGPP(argc, argv);

  LOG(INFO) << "Welcome to Intelevator, the intelligent elevator.";

  shared_ptr<Config> config(new Config());
  config->setFloors(10);
  config->setElevators(3);
  config->setMaxLoad(8);
  config->setDuration(100);
  config->setTitle("Here we go!");

  shared_ptr<Building> building(new Building(config));
  building->build();

  shared_ptr<Statistics> statistics(new Statistics(config));
  shared_ptr<Clock> clock(new Clock(config));
  shared_ptr<EventQueue> eventQueue(new EventQueue());
  shared_ptr<EventDispatcher> eventDispatcher(new EventDispatcher());

  Simulator simulator(config, building, statistics, clock, eventQueue, eventDispatcher);
  simulator.run();

  return 0;
}
