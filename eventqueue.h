#ifndef _EVENTQUEUE_H_
#define _EVENTQUEUE_H_

#include <queue>
#include "event.h"

class EventQueue {
private:
  std::priority_queue<Event> eventQueue;

public:
  void push(Event event);
  std::unique_ptr<Event> pop();
  std::unique_ptr<Event> peek();
};

#endif /* _EVENTQUEUE_H_ */
