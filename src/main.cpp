#include <iostream>
#include <memory>
#include "Config.h"
#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
  cout << "Welcome to Intelevator, the intelligent elevator" << endl;

  std::shared_ptr<Config> config;
  config->setFloors(10);
  config->setElevators(3);
  config->setMaxLoad(8);
  config->setDuration(100);
  config->setTitle("Here we go!");

  Simulator simulator(config);

  simulator.Run();

  return 0;
}
