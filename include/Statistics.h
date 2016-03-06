#pragma once

#include <list>
#include "Config.h"
#include "Trip.h"

class Statistics {
public:
  std::list<Trip*> trips;

  Statistics();
  void reset(Config config);
  bool keepRunning();
};