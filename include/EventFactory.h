#pragma once

#include <memory>
#include <string>

#include "Building.h"
#include "Clock.h"
#include "easylogging++.h"
#include "Event.h"
#include "EventType.h"

class EventFactory
{
public:
  EventFactory(const std::shared_ptr<Building> building, const std::shared_ptr<Clock> clock);
  virtual ~EventFactory();

  const std::shared_ptr<const Event> createEvent(EventType eventType) const;

private:
  std::shared_ptr<Building> _building;
  std::shared_ptr<Clock> _clock;
};
