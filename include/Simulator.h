#include <memory>
#include "Building.h"
#include "Clock.h"
#include "Config.h"
#include "EventDispatcher.h"
#include "EventQueue.h"
#include "Statistics.h"

class Simulator
{
public:
  Simulator(const std::shared_ptr<const Config> config);
  virtual ~Simulator();

  const std::shared_ptr<const Config> _config;
  Building _building;
  Statistics _statistics;
  Clock _clock;
  EventQueue _eventQueue;
  EventDispatcher _eventDispatcher;

  void Run();

private:
  bool NextStep();
};
