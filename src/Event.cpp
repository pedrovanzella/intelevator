#include "Event.h"

unsigned long Event::totalEvents = 0;

Event::Event(const unsigned long time, const EventType eventType)
  : _id(++Event::totalEvents)
  , _eventTime(time)
  , _eventType(eventType) {}

unsigned long Event::getId() const
{
  return _id;
}

unsigned long Event::getTime() const
{
  return _eventTime;
}

EventType Event::getType() const
{
  return _eventType;
}
