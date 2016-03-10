#include "Clock.h"

Clock::Clock(Config& config)
 : time(0.f)
 , config(config) {}

Clock::~Clock() {}

void Clock::reset(Config& config)
{
  this->time = 0;
  this->config = config;
}

float Clock::currentTime()
{
  return this->time;
}

void Clock::advanceTo(const float time)
{
  if (time <= this->time) return;
  this->time = time;
}

void Clock::advanceBy(const float ammount)
{
  if (ammount <= 0) return;
  this->time += ammount;
}

void Clock::notify(const Event& /*event*/)
{
  // Handle events
}