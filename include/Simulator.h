#pragma once

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
  Simulator(const std::shared_ptr<const Config> config,
            const std::shared_ptr<Building> building,
            const std::shared_ptr<Statistics> statistics,
            const std::shared_ptr<Clock> clock,
            const std::shared_ptr<EventQueue> eventQueue,
            const std::shared_ptr<EventDispatcher> EventDispatcher);
  virtual ~Simulator();
  void run();

private:
  bool nextStep();

  const std::shared_ptr<const Config> _config;
  const std::shared_ptr<Building> _building;
  const std::shared_ptr<Statistics> _statistics;
  const std::shared_ptr<Clock> _clock;
  const std::shared_ptr<EventQueue> _eventQueue;
  const std::shared_ptr<EventDispatcher> _eventDispatcher;
};
