#pragma once

#include "Building.h"
#include "Clock.h"
#include "EventDispatcher.h"
#include "EventQueue.h"
#include "Scenario.h"
#include "Statistics.h"
#include <memory>

class Simulator : public std::enable_shared_from_this<Simulator> {
public:
  Simulator(std::shared_ptr<const Scenario> scenario);
  virtual ~Simulator();

  const std::shared_ptr<const Scenario> getScenario() const;
  const std::shared_ptr<Statistics> getStatistics() const;
  const std::shared_ptr<Clock> getClock() const;
  const std::shared_ptr<EventQueue> getEventQueue() const;
  const std::shared_ptr<EventDispatcher> getEventDispatcher() const;

  void run();

private:
  const std::shared_ptr<const Scenario> _scenario;
  const std::shared_ptr<Statistics> _statistics;
  const std::shared_ptr<Clock> _clock;
  const std::shared_ptr<EventQueue> _eventQueue;
  const std::shared_ptr<EventDispatcher> _eventDispatcher;

  std::shared_ptr<Building> _building;

  bool nextStep();
};
