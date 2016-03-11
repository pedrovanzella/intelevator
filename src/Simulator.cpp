#include "Simulator.h"
#include <iostream>

void Simulator::Run()
{
  std::cout << "Simulator is running" << std::endl;
}

bool Simulator::NextStep()
{
  return true;
}

Simulator::Simulator(Config& config)
{
  
}
