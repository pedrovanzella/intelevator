#include "Event.h"
#include <string>
#include <sstream>

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

std::string Event::str() const
{
  std::ostringstream stream;
  stream << "#" << getId() << " (" << Helpers::eventTypeName(getType()) << ")";
  return stream.str();
}