#include "Building.h"
#include "Statistics.h"
#include "Clock.h"
#include "Config.h"

class Simulator
{
public:
  Building* _building;
  Statistics* _statistics;
  Clock* _clock;

  Simulator(Config& config);

  void Run();

private:
  bool NextStep();
};
