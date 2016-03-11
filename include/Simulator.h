#include "Building.h"
#include "Statistics.h"
#include "Clock.h"
#include "Config.h"

class Simulator
{
public:
  Building* building;
  Statistics* statistics;
  Clock* clock;

  Simulator(Config& config);

  void Run();

private:
  bool NextStep();
};
