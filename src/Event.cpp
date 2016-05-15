#include "Event.h"
#include <sstream>

unsigned long Event::totalEvents = 0;

Event::Event(const unsigned long time, const EventType type)
    : _id(++Event::totalEvents), _time(time), _type(type) {}

unsigned long Event::getId() const { return _id; }

unsigned long Event::getTime() const { return _time; }

EventType Event::getType() const { return _type; }

void Event::setTime(unsigned long time) {
  _time = time;
}

std::string Event::str() const {
  std::ostringstream stream;
  stream << "#" << getId() << " (" << Helpers::eventTypeName(getType()) << ")";
  return stream.str();
}