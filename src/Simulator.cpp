#include "Simulator.h"

#include <memory>
#include "easylogging++.h"

Simulator::Simulator(const std::shared_ptr<const Config> config,
                     const std::shared_ptr<Building> building,
                     const std::shared_ptr<Statistics> statistics,
                     const std::shared_ptr<Clock> clock,
                     const std::shared_ptr<EventQueue> eventQueue,
                     const std::shared_ptr<EventDispatcher> EventDispatcher)
  : _config(config)
  , _building(building)
  , _statistics(statistics)
  , _clock(clock)
  , _eventQueue(eventQueue)
  , _eventDispatcher(EventDispatcher)
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
  LOG(INFO) << "Simulator is running.";
  while (_statistics->keepRunning() && _eventQueue->hasNextEvent())
  {
    auto e = _eventQueue->pop();
    _eventDispatcher->broadcast(e);
  }
}

bool Simulator::nextStep()
{
  return true;
}

