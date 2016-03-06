#pragma once

#include "Config.h"

class Timer {
private:
  float time;

public:
  Timer();
  void reset(Config&);
  float currentTime();
  void advanceTo(float);
  void advanceBy(float);
};