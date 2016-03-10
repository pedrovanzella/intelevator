#pragma once

#include "Config.h"

class Timer {
private:
  float time;
  Config& config;

public:
  Timer(Config&);
  void reset(Config&);
  float currentTime();
  void advanceTo(const float);
  void advanceBy(const float);
};