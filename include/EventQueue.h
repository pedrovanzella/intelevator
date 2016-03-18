#pragma once

#include <memory>
#include <queue>
#include "Event.h"
#include "EventComparator.h"

class EventQueue {
public:
  EventQueue();
  ~EventQueue();

  bool hasNextEvent() const;
  void push(std::shared_ptr<const Event> event);
  std::shared_ptr<const Event> pop();
  std::shared_ptr<const Event> top() const;

private:
  std::priority_queue<std::shared_ptr<const Event>, std::vector<std::shared_ptr<const Event>>, EventComparator> _eventQueue;
};
