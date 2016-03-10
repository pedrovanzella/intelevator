#pragma once

#include "Config.h"
#include "EventObserver.h"

class Clock : public EventObserver
{
private:
  float time;
  Config& config;

public:
  Clock(Config&);
  virtual ~Clock();

  void reset(Config&);
  float currentTime();
  void advanceTo(const float);
  void advanceBy(const float);

  void notify(const Event&);
};