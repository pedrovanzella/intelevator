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

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event) const;

private:
  std::list<Trip*> _trips;
};
