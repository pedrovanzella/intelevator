#include <random>
#include "easylogging++.h"
#include "Scenario.h"
#include "Simulator.h"

Simulator::Simulator(const std::shared_ptr<const Scenario> scenario)
  : _scenario(scenario)
  , _statistics(std::shared_ptr<Statistics>(new Statistics()))
  , _clock(std::shared_ptr<Clock>(new Clock()))
  , _eventQueue(std::shared_ptr<EventQueue>(new EventQueue()))
  , _eventDispatcher(std::shared_ptr<EventDispatcher>(new EventDispatcher()))
{
  _building = _scenario->createBuilding();

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
  LOG(INFO) << "Running scenario '" << _scenario->getName() << "'.";
  while (_statistics->keepRunning() && _eventQueue->hasNextEvent())
  {
    auto e = _eventQueue->pop();
    _eventDispatcher->broadcast(e);
  }
  LOG(INFO) << "Finished scenario '" << _scenario->getName() << "'.";
}

bool Simulator::nextStep()
{
  return true;
}

