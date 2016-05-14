#pragma once

#include <memory>

class Event;
class EventObserver;

class EventNotifier {
protected:
  virtual void subscribe(std::shared_ptr<EventObserver> observer) = 0;
  virtual void unsubscribe(std::shared_ptr<EventObserver> observer) = 0;
  virtual void broadcast(const std::shared_ptr<const Event> event) const = 0;
};
