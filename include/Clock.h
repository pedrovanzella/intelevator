#pragma once

#include <memory>
#include "Config.h"
#include "EventObserver.h"

class Clock : public EventObserver
{
public:
  Clock(const std::shared_ptr<const Config> config);
  virtual ~Clock();

  float currentTime() const;
  void advanceTo(const float time);
  void advanceBy(const float amount);

  void notify(const std::shared_ptr<const Event> event) const;

private:
  float _time;
  const std::shared_ptr<const Config> _config;
};
