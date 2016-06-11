#include "Clock.h"
#include "Event.h"
#include <sstream>
#include <glog/logging.h>

Clock::Clock() : _time(0) {}

Clock::Clock(const Clock& clock) : _time(clock.currentTime()) {}

Clock::~Clock() {}

unsigned long Clock::currentTime() const { return _time; }

void Clock::advanceTo(const unsigned long time) {
  if (time <= _time)
    return;
  _time = time;
}

void Clock::advanceBy(const unsigned long amount) {
  if (amount <= 0)
    return;
  _time += amount;
}

void Clock::notify(const std::shared_ptr<const Event> event) {
  advanceTo(event->getTime());
}

std::string Clock::str() const {
  std::ostringstream stream;
  stream << "t=" << _time;
  return stream.str();
}