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
  , _eventFactory(std::shared_ptr<EventFactory>(new EventFactory(_scenario, _clock, _eventQueue)))
{
  _building = _scenario->createBuilding();

  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));

  auto destination = _building->getFloors()->back()->getNumber();
  const auto client = std::shared_ptr<const Client>(new Client(1, 10, destination));

  auto location = _building->getFloors()->front()->getNumber();
  auto ca = std::shared_ptr<ClientArrival>(new ClientArrival(10, client, location));

  _eventQueue->push(std::static_pointer_cast<Event>(ca));
}

Simulator::~Simulator()
{}

void Simulator::run()
{
  LOG(INFO) << "Running scenario '" << _scenario->getName() << "'.";
  while (_statistics->keepRunning() && _eventQueue->hasNextEvent())
  {
    auto e = _eventQueue->pop();
    if (e)
      _eventDispatcher->broadcast(e);
  }
  LOG(INFO) << "Finished scenario '" << _scenario->getName() << "'.";
}

bool Simulator::nextStep()
{
  return true;
}

