#pragma once

#include "EventObserver.h"
#include <memory>
#include <string>

class Clock : public EventObserver {
public:
  Clock();
  Clock(const Clock& clock);
  virtual ~Clock();

  unsigned long currentTime() const;

  void advanceTo(const unsigned long time);
  void advanceBy(const unsigned long amount);
  void notify(const std::shared_ptr<const Event> event);
  std::string str() const;

private:
  unsigned long _time;
};
