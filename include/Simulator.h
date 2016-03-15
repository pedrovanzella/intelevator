#include "Building.h"
#include "Clock.h"
#include "Config.h"
#include "EventDispatcher.h"
#include "EventQueue.h"
#include "Statistics.h"

class Simulator
{
public:
  Simulator(Config& config);
  virtual ~Simulator();

  Config _config;
  Building _building;
  Statistics _statistics;
  Clock _clock;
  EventQueue _eventQueue;
  EventDispatcher _eventDispatcher;

  void Run();

private:
  bool NextStep();
};
