#pragma once

#include "Event.h"

class EventObserver
{
public:
  virtual void notify(Event*) = 0;
};