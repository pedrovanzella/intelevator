#pragma once

#include <queue>
#include "Event.h"
#include "EventComparator.h"

class EventQueue {
private:
  std::priority_queue<Event*, std::vector<Event*>, EventComparator> eventQueue;

public:
  EventQueue();
  ~EventQueue();

  bool hasNextEvent();
  void push(Event*);
  Event* pop();
  Event* top();
};