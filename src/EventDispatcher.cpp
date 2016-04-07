#include "easylogging++.h"
#include "EventDispatcher.h"

EventDispatcher::EventDispatcher()
{}

EventDispatcher::~EventDispatcher()
{}

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
  LOG(INFO) << "Broadcasting event " << event->str() << ".";
  for (auto &it : _observers) {
    it->notify(event);
  }
}
