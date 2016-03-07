#pragma once

#include "Event.h"

class EventObserver
{
public:
  virtual void notify(const Event&) = 0;
};