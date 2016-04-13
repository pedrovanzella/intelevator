#pragma once

#include "Event.h"
#include "EventComparator.h"
#include <memory>
#include <queue>

class EventQueue {
public:
  EventQueue();
  virtual ~EventQueue();

  bool hasNextEvent() const;
  std::shared_ptr<const Event> top() const;
  std::shared_ptr<const Event> pop();
  void push(std::shared_ptr<const Event> event);

private:
  std::priority_queue<std::shared_ptr<const Event>, std::vector<std::shared_ptr<const Event>>, EventComparator> _eventQueue;
};
