#pragma once

#include <memory>
#include "Config.h"
#include "EventObserver.h"

class Clock : public EventObserver
{
public:
  Clock(const std::shared_ptr<const Config> config);
  virtual ~Clock();

  unsigned long currentTime() const;
  void advanceTo(const unsigned long time);
  void advanceBy(const unsigned long amount);

  void notify(const std::shared_ptr<const Event> event) const;

private:
  unsigned long _time;
  const std::shared_ptr<const Config> _config;
};
