#pragma once

#include <memory>
#include "easylogging++.h"
#include "Clock.h"
#include "EventQueue.h"
#include "Scenario.h"

class EventFactory
{
public:
  EventFactory(const std::shared_ptr<const Scenario> scenario,
               const std::shared_ptr<Clock> clock,
               const std::shared_ptr<EventQueue> queue);
  virtual ~EventFactory();

private:
  const std::shared_ptr<const Scenario> _scenario;
  const std::shared_ptr<Clock> _clock;
  const std::shared_ptr<EventQueue> _queue;

};
