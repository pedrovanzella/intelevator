#pragma once

#include "Elevator.h"
#include "Event.h"
#include "Floor.h"
#include "Trip.h"
#include <list>
#include <memory>

class Statistics : public EventObserver {
public:
  Statistics();
  virtual ~Statistics();

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event);

  void addTrip(const unsigned long dropOffTime,
               const std::shared_ptr<Elevator> elevator,
               const std::shared_ptr<Client> passenger);

private:
  std::vector<Trip> _trips;
};
