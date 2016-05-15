#pragma once

#include "EventType.h"
#include <string>

class Event {
public:
  static unsigned long totalEvents;

  Event(unsigned long time, EventType type);
  unsigned long getId() const;
  unsigned long getTime() const;
  EventType getType() const;

  void setTime(unsigned long time);

  virtual std::string str() const;

protected:
  unsigned long _id;
  unsigned long _time;
  EventType _type;
};
