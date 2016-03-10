#pragma once

#include <list>
#include "Config.h"
#include "EventObserver.h"
#include "Trip.h"

class Statistics : public EventObserver
{
public:
  Statistics(Config&);

  void reset(Config& config);
  bool keepRunning();
  void notify(const Event&);

private:
  Config& config;
  std::list<Trip*> trips;
};