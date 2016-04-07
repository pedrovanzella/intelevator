#include "EventFactory.h"

EventFactory::EventFactory(const std::shared_ptr<const Scenario> scenario,
                           const std::shared_ptr<Clock> clock,
                           const std::shared_ptr<EventQueue> queue)
  : _scenario(scenario)
  , _clock(clock)
  , _queue(queue)
{}

EventFactory::~EventFactory()
{}
