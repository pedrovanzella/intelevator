#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
}

void EventDispatcher::subscribe(EventObserver* eventObserver)
{
  if (eventObserver == nullptr) return;
  _observers.push_back(eventObserver);
}

void EventDispatcher::unsubscribe(EventObserver* eventObserver)
{
  if (eventObserver == nullptr) return;
  _observers.remove(eventObserver);
}

void EventDispatcher::broadcast(const Event& event) const
{
  for (auto &it : _observers) {
    it->notify(event);
  }
}
