#include "Simulator.h"
#include "easylogging++.h"
#include <random>

Simulator::Simulator(const std::shared_ptr<const Config> config,
                     const std::shared_ptr<Building> building,
                     const std::shared_ptr<Statistics> statistics,
                     const std::shared_ptr<Clock> clock,
                     const std::shared_ptr<EventQueue> eventQueue,
                     const std::shared_ptr<EventDispatcher> eventDispatcher,
                     const std::shared_ptr<EventFactory> eventFactory)
  : _config(config)
  , _building(building)
  , _statistics(statistics)
  , _clock(clock)
  , _eventQueue(eventQueue)
  , _eventDispatcher(eventDispatcher)
  , _eventFactory(eventFactory)
{
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));
}

Simulator::~Simulator()
{
  _eventDispatcher->unsubscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->unsubscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->unsubscribe(std::static_pointer_cast<EventObserver>(_clock));
}

void Simulator::run()
{
  _eventFactory->initialize();
  LOG(INFO) << "Simulation started.";
  while (_statistics->keepRunning() && _eventQueue->hasNextEvent())
  {
    auto e = _eventQueue->pop();
    _eventDispatcher->broadcast(e);
  }
  LOG(INFO) << "Simulation completed.";
}

bool Simulator::nextStep()
{
  return true;
}

