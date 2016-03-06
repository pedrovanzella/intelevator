#pragma once

#include <list>
#include "trip.h"
#include "config.h"

class Statistics {
public:
  std::list<std::shared_ptr<Trip>> trips;

  void reset(Config config);
  bool keepRunning();
};