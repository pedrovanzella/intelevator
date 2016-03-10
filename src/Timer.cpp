#include "Timer.h"

Timer::Timer(Config& config)
 : time(0.f)
 , config(config)
{
}

void Timer::reset(Config& config)
{
  this->time = 0;
  this->config = config;
}

float Timer::currentTime()
{
  return this->time;
}

void Timer::advanceTo(const float time)
{
  if (time <= this->time) return;
  this->time = time;
}

void Timer::advanceBy(const float ammount)
{
  if (ammount <= 0) return;
  this->time += ammount;
}
