#pragma once

#include "EventType.h"

class Event {
public:
  static unsigned long totalEvents;

  Event(float, EventType);
  unsigned long getId();
  float getTime();
  EventType getType();

protected:
  unsigned long id;
  float eventTime;
  EventType eventType;
};