#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
}

void EventDispatcher::subscribe(std::shared_ptr<const EventObserver> eventObserver)
{
  if (eventObserver == nullptr) return;
  _observers.push_back(eventObserver);
}

void EventDispatcher::unsubscribe(std::shared_ptr<const EventObserver> eventObserver)
{
  if (eventObserver == nullptr) return;
  _observers.remove(eventObserver);
}

void EventDispatcher::broadcast(const std::shared_ptr<const Event> event) const
{
  for (auto &it : _observers) {
    it->notify(event);
  }
}
