#pragma once

#include <list>
#include <memory>
#include "Config.h"
#include "EventObserver.h"
#include "Trip.h"

class Statistics : public EventObserver
{
public:
  Statistics(Config&);

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event) const;

private:
  Config& _config;
  std::list<Trip*> _trips;
};
