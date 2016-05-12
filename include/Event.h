#pragma once

#include "EventType.h"

class Event {
public:
  static unsigned long totalEvents;

  Event(unsigned long time, EventType eventType);
  unsigned long getId() const;
  unsigned long getTime() const;
  EventType getType() const;

  virtual std::string str() const;

protected:
  unsigned long _id;
  unsigned long _eventTime;
  EventType _eventType;
};
