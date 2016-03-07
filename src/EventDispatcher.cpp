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

void EventDispatcher::notify(const Event& event)
{
  for (auto it = this->observers.begin(); it != this->observers.end(); ++it)
    (*it)->notify(event);
}
