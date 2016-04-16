#include "EventQueue.h"
#include <glog/logging.h>

EventQueue::EventQueue() {}

EventQueue::~EventQueue() {
  while (!_eventQueue.empty()) {
    _eventQueue.pop();
  }
}

bool EventQueue::hasNextEvent() const { return !_eventQueue.empty(); }

std::shared_ptr<const Event> EventQueue::top() const {
  if (_eventQueue.empty())
    return std::shared_ptr<const Event>(nullptr);

  return _eventQueue.top();
}

std::shared_ptr<const Event> EventQueue::pop() {
  if (_eventQueue.empty())
    return std::shared_ptr<const Event>(nullptr);

  std::shared_ptr<const Event> event = _eventQueue.top();
  _eventQueue.pop();

  return event;
}

void EventQueue::push(std::shared_ptr<const Event> event) {
  _eventQueue.push(event);
}
