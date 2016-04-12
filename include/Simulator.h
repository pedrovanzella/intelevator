#pragma once

#include <memory>
#include "Building.h"
#include "Clock.h"
#include "EventDispatcher.h"
#include "EventFactory.h"
#include "EventQueue.h"
#include "Statistics.h"

class Simulator
{
public:
  Simulator(std::shared_ptr<const Scenario> scenario);
  virtual ~Simulator();

  const std::shared_ptr<const Scenario> getScenario() const;
  const std::shared_ptr<Statistics> getStatistics() const;
  const std::shared_ptr<Clock> getClock() const;
  const std::shared_ptr<EventQueue> getEventQueue() const;
  const std::shared_ptr<EventDispatcher> getEventDispatcher() const;
  const std::shared_ptr<EventFactory> getEventFactory() const;

  void run();

private:
  bool nextStep();

  const std::shared_ptr<const Scenario> _scenario;
  const std::shared_ptr<Statistics> _statistics;
  const std::shared_ptr<Clock> _clock;
  const std::shared_ptr<EventQueue> _eventQueue;
  const std::shared_ptr<EventDispatcher> _eventDispatcher;
  const std::shared_ptr<EventFactory> _eventFactory;

  std::shared_ptr<Building> _building;
};
