#pragma once

#include "EventNotifier.h"
#include <list>
#include <memory>

class Event;         // forward declaration
class EventObserver; // forward declaration

class EventDispatcher : public EventNotifier {
public:
  EventDispatcher();
  virtual ~EventDispatcher();

  void broadcast(const std::shared_ptr<const Event> event) const;

  void subscribe(std::shared_ptr<EventObserver> eventObserver);
  void unsubscribe(std::shared_ptr<EventObserver> eventObserver);

private:
  std::list<std::shared_ptr<EventObserver>> _observers;
};
