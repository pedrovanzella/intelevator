#pragma once

#include <memory>

class Event; // forward declaration

class EventObserver {
public:
  virtual void notify(const std::shared_ptr<const Event> event) = 0;
};
