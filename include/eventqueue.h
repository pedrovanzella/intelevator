#pragma once

#include <queue>
#include "event.h"

class EventQueue {
private:
  std::priority_queue<std::shared_ptr<Event>> eventQueue;

public:
  void push(std::shared_ptr<Event> event);
  std::shared_ptr<Event> pop();
  std::shared_ptr<Event> peek();
};