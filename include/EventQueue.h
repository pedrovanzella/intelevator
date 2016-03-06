#pragma once

#include <queue>
#include "Event.h"

class EventQueue {
private:
  std::priority_queue<Event*> eventQueue;

public:
  void push(Event*);
  Event* pop();
  Event* peek();
};