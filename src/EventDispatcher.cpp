#include "EventDispatcher.h"
#include "Event.h"
#include "EventObserver.h"

EventDispatcher::EventDispatcher() {}

EventDispatcher::~EventDispatcher() {}

void EventDispatcher::broadcast(const std::shared_ptr<const Event> event) const {
  if (event) {
    for (auto &it : _observers) {
      it->notify(event);
    }
  }
}

void EventDispatcher::subscribe(std::shared_ptr<EventObserver> eventObserver) {
  if (eventObserver)
    _observers.push_back(eventObserver);
}

void EventDispatcher::unsubscribe(std::shared_ptr<EventObserver> eventObserver) {
  if (eventObserver)
    _observers.remove(eventObserver);
}
