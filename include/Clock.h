#pragma once

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

  void notify(const Event&) const;

private:
  float _time;
  Config& _config;
};
