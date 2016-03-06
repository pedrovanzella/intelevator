#pragma once

#include "EventObserver.h"
#include "EventNotifier.h"
#include "Event.h"

class EventDispatcher : public EventNotifier
{
public:
  EventDispatcher();

  void subscribe(EventObserver&);
  void unsubscribe(EventObserver&);
  void notify(Event&);
};