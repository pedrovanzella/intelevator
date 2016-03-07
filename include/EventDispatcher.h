#pragma once

#include <list>

#include "EventObserver.h"
#include "EventNotifier.h"
#include "Event.h"

class EventDispatcher : public EventNotifier
{
public:
  EventDispatcher();

  void subscribe(EventObserver*);
  void unsubscribe(EventObserver*);
  void notify(const Event&);

private:
  std::list<EventObserver*> observers;
};