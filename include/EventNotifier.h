#pragma once

#include <memory>
#include "Event.h"
#include "EventObserver.h"

class EventNotifier
{
protected:
  virtual void subscribe(std::shared_ptr<const EventObserver> observer) = 0;
  virtual void unsubscribe(std::shared_ptr<const EventObserver> observer) = 0;
  virtual void broadcast(const std::shared_ptr<const Event> event) const = 0;
};
