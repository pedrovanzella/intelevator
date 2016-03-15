#pragma once

#include "EventType.h"

class Event {
public:
  static unsigned long totalEvents;

  Event(float time, EventType eventType);
  unsigned long getId() const;
  float getTime() const;
  EventType getType() const;

protected:
  unsigned long _id;
  float _eventTime;
  EventType _eventType;
};
