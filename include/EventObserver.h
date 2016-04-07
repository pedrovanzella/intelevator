#pragma once

#include <memory>
#include "Event.h"

class EventObserver
{
public:
  virtual void notify(const std::shared_ptr<const Event> event) = 0;
};
