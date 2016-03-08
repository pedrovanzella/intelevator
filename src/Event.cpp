#include "Event.h"

unsigned long Event::totalEvents = 0;

Event::Event(EventType type, float time)
  : eventType(type)
  , eventTime(time)
  , id(++Event::totalEvents)
  {}
