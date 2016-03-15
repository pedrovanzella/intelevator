#pragma once

#include "Event.h"
#include "EventObserver.h"

class EventNotifier
{
protected:
  virtual void subscribe(EventObserver*) = 0;
  virtual void unsubscribe(EventObserver*) = 0;
  virtual void broadcast(const Event&) const = 0;
};
