#include <random>
#include <glog/logging.h>
#include "Scenario.h"
#include "Simulator.h"

#include "ClientArrival.h"
#include "CycleElevators.h"

Simulator::Simulator(const std::shared_ptr<const Scenario> scenario)
  : _scenario(scenario)
  , _statistics(std::shared_ptr<Statistics>(new Statistics()))
  , _clock(std::shared_ptr<Clock>(new Clock()))
  , _eventQueue(std::shared_ptr<EventQueue>(new EventQueue()))
  , _eventDispatcher(std::shared_ptr<EventDispatcher>(new EventDispatcher()))
  , _eventFactory(std::shared_ptr<EventFactory>(new EventFactory(_scenario, _clock, _eventQueue))) {}

Simulator::~Simulator()
{}

const std::shared_ptr<const Scenario> Simulator::getScenario() const { return _scenario; }
const std::shared_ptr<Statistics> Simulator::getStatistics() const { return _statistics; }
const std::shared_ptr<Clock> Simulator::getClock() const { return _clock; }
const std::shared_ptr<EventQueue> Simulator::getEventQueue() const { return _eventQueue; }
const std::shared_ptr<EventDispatcher> Simulator::getEventDispatcher() const { return _eventDispatcher; }
const std::shared_ptr<EventFactory> Simulator::getEventFactory() const { return _eventFactory; }

void Simulator::run()
{
  _building = _scenario->createBuilding();

  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));

  auto ca1 = std::shared_ptr<ClientArrival>(new ClientArrival(10, std::make_shared<const Client>(1, 0, 5)));
  auto ca2 = std::shared_ptr<ClientArrival>(new ClientArrival(20, std::make_shared<const Client>(1, 3, 1)));

  _eventQueue->push(std::static_pointer_cast<Event>(ca1));
  _eventQueue->push(std::static_pointer_cast<Event>(ca2));

  LOG(INFO) << "Running '" << _scenario->getName() << "' scenario.";
  while (_statistics->keepRunning() && _eventQueue->hasNextEvent())
  {
    auto e = _eventQueue->pop();
    if (e)
      _eventDispatcher->broadcast(e);
  }
  LOG(INFO) << "Finished '" << _scenario->getName() << "' scenario.";
}

bool Simulator::nextStep()
{
  return true;
}

