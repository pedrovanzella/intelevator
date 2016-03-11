#pragma once

#include "EventType.h"

class Event {
public:
  static unsigned long totalEvents;

  Event(float, EventType);
  unsigned long getId() const;
  float getTime() const;
  EventType getType() const;

protected:
  unsigned long id;
  float eventTime;
  EventType eventType;
};
