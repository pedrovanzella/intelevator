#include "easylogging++.h"
#include "EventQueue.h"

EventQueue::EventQueue()
{}

EventQueue::~EventQueue()
{
  while(!_eventQueue.empty())
  {
    _eventQueue.pop();
  }
}

bool EventQueue::hasNextEvent() const
{
  return !_eventQueue.empty();
}

void EventQueue::push(std::shared_ptr<const Event> event)
{
  _eventQueue.push(event);

  LOG(INFO) << "Scheduled event " << event->str() << ".";
}

std::shared_ptr<const Event> EventQueue::pop()
{
  if (_eventQueue.empty()) return std::shared_ptr<const Event>(nullptr);

  std::shared_ptr<const Event> event = _eventQueue.top();
  _eventQueue.pop();

  return event;
}

std::shared_ptr<const Event> EventQueue::top() const
{
  if (_eventQueue.empty()) return std::shared_ptr<const Event>(nullptr);

  return _eventQueue.top();
}
