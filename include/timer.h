#pragma once

#include "config.h"

class Timer {
private:
  float time;

public:
  void reset(std::shared_ptr<Config> config);
  float currentTime();
  void advanceTo(float time);
  void advanceBy(float ammount);
};