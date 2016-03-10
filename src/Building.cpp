#include "Building.h"
#include "Elevator.h"
#include "Floor.h"

Building::Building(Config& config)
 : config(config)
{
  this->reset(config);
}

Building::~Building()
{
  Floor* f = nullptr;
  while(!floors.empty())
  {
    f = floors.back();
    floors.pop_back();
    delete f;
  }

  Elevator* e = nullptr;
  while(!elevators.empty())
  {
    e = elevators.back();
    elevators.pop_back();
    delete e;
  }
}

void Building::reset(Config& config)
{
  this->config = config;

  for (int i = 0; i < config.floors; i++)
  {
    Floor* f = new Floor(*this, i);
    floors.push_back(f);
  }

  Floor* lobby = floors.front();

  for (int i = 0; i < config.elevators; i++)
  {
    Elevator* e = new Elevator(*this, *lobby);
    elevators.push_back(e);
  }
}

const Config& Building::getConfig()
{
  return config;
}
