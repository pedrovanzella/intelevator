#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
}

void EventDispatcher::subscribe(EventObserver* eventObserver)
{
  if (eventObserver == nullptr) return;
  this->observers.push_back(eventObserver);
}

void EventDispatcher::unsubscribe(EventObserver* eventObserver)
{
  if (eventObserver == nullptr) return;
  this->observers.remove(eventObserver);
}

void EventDispatcher::notify(const Event& event) const
{
  for (auto &it : this->observers) {
    it->notify(event);
  }
}
