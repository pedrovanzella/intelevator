#pragma once

#include <memory>
#include "EventObserver.h"

class Clock : public EventObserver
{
public:
  Clock();
  virtual ~Clock();

  unsigned long currentTime() const;
  void advanceTo(const unsigned long time);
  void advanceBy(const unsigned long amount);

  void notify(const std::shared_ptr<const Event> event) const;

private:
  unsigned long _time;
};
