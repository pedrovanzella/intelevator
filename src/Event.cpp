#include "Event.h"

unsigned long Event::totalEvents = 0;

Event::Event(const float time, const EventType eventType)
  : id(++Event::totalEvents)
  , eventTime(time)
  , eventType(eventType) {}

unsigned long Event::getId()
{
  return this->id;
}

float Event::getTime()
{
  return this->eventTime;
}

EventType Event::getType()
{
  return this->eventType;
}
