#pragma once

#include <queue>
#include "Event.h"
#include "EventComparator.h"

class EventQueue {
public:
  EventQueue();
  ~EventQueue();

  bool hasNextEvent() const;
  void push(Event*);
  Event* pop();
  Event* top() const;

private:
  std::priority_queue<Event*, std::vector<Event*>, EventComparator> _eventQueue;
};
