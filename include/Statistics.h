#pragma once

#include <list>
#include <memory>
#include "Config.h"
#include "EventObserver.h"
#include "Trip.h"

class Statistics : public EventObserver
{
public:
  Statistics(const std::shared_ptr<const Config> config);

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event) const;

private:
  const std::shared_ptr<const Config> _config;
  std::list<Trip*> _trips;
};
