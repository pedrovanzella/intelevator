#include <iostream>

#include "Config.h"

#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
  cout << "Welcome to Intelevator, the intelligent elevator" << endl;

  Config config;
  config.floors = 10;
  config.elevators = 3;
  config.maxLoad = 8;
  config.duration = 100;
  config.title = "Here we go!";

  Simulator simulator(config);

  simulator.Run();

  return 0;
}
