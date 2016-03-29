#include "Clock.h"
#include "easylogging++.h"

Clock::Clock(const std::shared_ptr<const Config> config)
 : _time(0)
 , _config(config)
{
  LOG(TRACE) << "Clock created.";
}

Clock::~Clock()
{
  LOG(TRACE) << "Clock created.";
}

unsigned long Clock::currentTime() const
{
  return _time;
}

void Clock::advanceTo(const unsigned long time)
{
  if (time <= _time) return;
  _time = time;
}

void Clock::advanceBy(const unsigned long amount)
{
  if (amount <= 0) return;
  _time += amount;
}

void Clock::notify(const std::shared_ptr<const Event> event) const
{
  // Handle events
}
