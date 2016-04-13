#pragma once

#include "EventObserver.h"
#include <memory>

class Clock : public EventObserver {
public:
  Clock();
  virtual ~Clock();

  unsigned long currentTime() const;

  void advanceTo(const unsigned long time);
  void advanceBy(const unsigned long amount);
  void notify(const std::shared_ptr<const Event> event);

private:
  unsigned long _time;
};
