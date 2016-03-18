#pragma once

#include <memory>
#include "Config.h"
#include "EventObserver.h"

class Clock : public EventObserver
{
public:
  Clock(Config&);
  virtual ~Clock();

  float currentTime() const;
  void advanceTo(const float time);
  void advanceBy(const float amount);

  void notify(const std::shared_ptr<const Event> event) const;

private:
  float _time;
  Config& _config;
};
