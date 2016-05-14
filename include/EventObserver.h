#pragma once

#include "Event.h"
#include <memory>

class EventObserver {
public:
  virtual void notify(const std::shared_ptr<const Event> event) = 0;
};
