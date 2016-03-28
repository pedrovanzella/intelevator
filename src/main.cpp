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
  config->setInt(Property::Floors, 10);
  config->setInt(Property::Elevators, 3);
  config->setInt(Property::MaxLoad, 8);
  config->setFloat(Property::Duration, 100);
  config->setString(Property::Title, "Here we go!");

  shared_ptr<Building> building(new Building(config));
  building->initialize();

  shared_ptr<Statistics> statistics(new Statistics(config));
  shared_ptr<Clock> clock(new Clock(config));
  shared_ptr<EventQueue> eventQueue(new EventQueue());
  shared_ptr<EventDispatcher> eventDispatcher(new EventDispatcher());
  shared_ptr<EventFactory> eventFactory(new EventFactory(building, clock));

  Simulator simulator(config, building, statistics, clock, eventQueue, eventDispatcher, eventFactory);
  simulator.run();

  return 0;
}
