#pragma once

#include "Event.h"
#include "EventComparator.h"
#include <memory>
#include <queue>

class Clock; // forward declaration

class EventQueue {
public:
  EventQueue();
  virtual ~EventQueue();

  bool hasNextEvent() const;
  std::shared_ptr<Event> top() const;
  std::shared_ptr<Event> pop();
  void push(std::shared_ptr<Event> event);

  void refresh(const unsigned long currentTime);

private:
  std::priority_queue<std::shared_ptr<Event>,
                      std::vector<std::shared_ptr<Event>>,
                      EventComparator> _eventQueue;
};
