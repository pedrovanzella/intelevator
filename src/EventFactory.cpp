#include "EventFactory.h"

#include "ClientArrival.h"
#include "ElevatorArrival.h"

EventFactory::EventFactory(const std::shared_ptr<const Config> config,
                           const std::shared_ptr<Building> building,
                           const std::shared_ptr<Clock> clock)
  : _config(config)
  , _building(building)
  , _clock(clock)
{
  LOG(TRACE) << "EventFactory created.";
}

EventFactory::~EventFactory()
{
  LOG(TRACE) << "EventFactory destroyed.";
}

const std::shared_ptr<const Event> EventFactory::createEvent(EventType eventType) const
{
  throw "Now implemented yet.";
}