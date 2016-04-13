#pragma once

#include <list>
#include <memory>
#include "EventObserver.h"
#include "Trip.h"

class Statistics : public EventObserver
{
public:
  Statistics();
  virtual ~Statistics();

  void addTrip(Trip);

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event);

private:
  std::vector<Trip> _trips;
};
