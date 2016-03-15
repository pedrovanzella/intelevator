#include <iostream>

#include "Config.h"

#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[])
{
  cout << "Welcome to Intelevator, the intelligent elevator" << endl;

  Config config;
  config._floors = 10;
  config._elevators = 3;
  config._maxLoad = 8;
  config._duration = 100;
  config._title = "Here we go!";

  Simulator simulator(config);

  simulator.Run();

  return 0;
}
