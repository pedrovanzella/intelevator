#include "EventQueue.h"

EventQueue::EventQueue()
{
}

EventQueue::~EventQueue()
{
  while (!_eventQueue.empty())
  {
    Event* e = this->pop();
    if (e != nullptr)
      delete e;
  }
}

bool EventQueue::hasNextEvent() const
{
  return !_eventQueue.empty();
}

void EventQueue::push(Event* event)
{
  _eventQueue.push(event);
}

Event* EventQueue::pop()
{
  if (_eventQueue.empty()) return nullptr;

  Event* event = _eventQueue.top();
  _eventQueue.pop();

  return event;
}

Event* EventQueue::top() const
{
  if (_eventQueue.empty()) return nullptr;

  return _eventQueue.top();
}
