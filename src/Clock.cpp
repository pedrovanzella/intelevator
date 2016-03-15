#include "Clock.h"

Clock::Clock(Config& config)
 : _time(0.f)
 , _config(config) {}

Clock::~Clock() {}

float Clock::currentTime() const
{
  return _time;
}

void Clock::advanceTo(const float time)
{
  if (time <= _time) return;
  _time = time;
}

void Clock::advanceBy(const float amount)
{
  if (amount <= 0) return;
  _time += amount;
}

void Clock::notify(const Event& /*event*/) const
{
  // Handle events
}
