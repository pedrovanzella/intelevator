#pragma once

#include <list>
#include <memory>

#include "EventObserver.h"
#include "EventNotifier.h"
#include "Event.h"

class EventDispatcher : public EventNotifier
{
public:
  EventDispatcher();
  virtual ~EventDispatcher();

  void subscribe(std::shared_ptr<EventObserver> eventObserver);
  void unsubscribe(std::shared_ptr<EventObserver> eventObserver);
  void broadcast(const std::shared_ptr<const Event> event) const;

private:
  std::list<std::shared_ptr<EventObserver>> _observers;
};
