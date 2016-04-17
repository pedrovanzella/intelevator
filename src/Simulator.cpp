#include "Simulator.h"
#include "ClientArrival.h"
#include "CycleElevators.h"
#include <glog/logging.h>
#include <random>

Simulator::Simulator(const std::shared_ptr<const Scenario> scenario)
    : _scenario(scenario), _statistics(std::make_shared<Statistics>()),
      _clock(std::make_shared<Clock>()),
      _eventQueue(std::make_shared<EventQueue>()),
      _eventDispatcher(std::make_shared<EventDispatcher>()) {}

Simulator::~Simulator() {}

const std::shared_ptr<const Scenario> Simulator::getScenario() const { return _scenario; }

const std::shared_ptr<Statistics> Simulator::getStatistics() const { return _statistics; }

const std::shared_ptr<Clock> Simulator::getClock() const { return _clock; }

const std::shared_ptr<EventQueue> Simulator::getEventQueue() const { return _eventQueue; }

const std::shared_ptr<EventDispatcher> Simulator::getEventDispatcher() const { return _eventDispatcher; }

void Simulator::run() {
  LOG(INFO) << "Running '" << _scenario->getName() << "' scenario.";

  _building = _scenario->createBuilding(shared_from_this());

  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));

  auto ca1 = std::make_shared<ClientArrival>(10, std::make_shared<Client>(1, 0, 5, _clock->currentTime()));
  auto ca2 = std::make_shared<ClientArrival>(20, std::make_shared<Client>(1, 3, 1, _clock->currentTime()));
  auto ca3 = std::make_shared<ClientArrival>(30, std::make_shared<Client>(1, 5, 2, _clock->currentTime()));

  _eventQueue->push(std::static_pointer_cast<Event>(ca1));
  _eventQueue->push(std::static_pointer_cast<Event>(ca2));
  _eventQueue->push(std::static_pointer_cast<Event>(ca3));

  while (_statistics->keepRunning() && _eventQueue->hasNextEvent()) {
    auto e = _eventQueue->pop();
    if (e)
      _eventDispatcher->broadcast(e);
  }

  LOG(INFO) << "Finished '" << _scenario->getName() << "' scenario.";
}

bool Simulator::nextStep() { return true; }