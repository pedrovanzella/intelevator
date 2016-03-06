#ifndef _EVENTQUEUE_H_
#define _EVENTQUEUE_H_

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

#endif /* _EVENTQUEUE_H_ */
