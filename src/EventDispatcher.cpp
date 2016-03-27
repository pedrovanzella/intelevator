#include "easylogging++.h"
#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{
  LOG(TRACE) << "EventDispatcher created.";
}

EventDispatcher::~EventDispatcher()
{
  LOG(TRACE) << "EventDispatcher destroyed.";
}

void EventDispatcher::subscribe(std::shared_ptr<EventObserver> eventObserver)
{
  if (eventObserver == nullptr) return;
  _observers.push_back(eventObserver);
}

void EventDispatcher::unsubscribe(std::shared_ptr<EventObserver> eventObserver)
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
