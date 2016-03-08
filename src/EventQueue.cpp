#include "EventQueue.h"

EventQueue::EventQueue()
{
}

EventQueue::~EventQueue()
{
  while (!this->eventQueue.empty())
  {
    Event* e = this->pop();
    if (e != nullptr)
      delete e;
  }
}

bool EventQueue::hasNextEvent()
{
  return this->eventQueue.empty();
}

void EventQueue::push(Event* event)
{
  this->eventQueue.push(event);
}

Event* EventQueue::pop()
{
  if (this->eventQueue.empty()) return nullptr;

  Event* event = this->eventQueue.top();
  this->eventQueue.pop();

  return event;
}

Event* EventQueue::top()
{
  if (this->eventQueue.empty()) return nullptr;

  return this->eventQueue.top();
}
