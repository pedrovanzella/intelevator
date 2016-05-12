#pragma once

#include "Elevator.h"
#include "Event.h"
#include "Floor.h"
#include "Trip.h"
#include <list>
#include <memory>
#include <string>
#include <fstream>

class Statistics : public EventObserver {
public:
  Statistics();
  virtual ~Statistics();

  bool keepRunning() const;
  void notify(const std::shared_ptr<const Event> event);

  void logDropOff(const unsigned long dropOffTime,
                  std::shared_ptr<Elevator> elevator,
                  std::shared_ptr<std::vector<std::shared_ptr<Client>>> droppedPassengers);

  void addTrip(const unsigned long dropOffTime,
               const std::shared_ptr<Elevator> elevator,
               const std::shared_ptr<Client> passenger);

  void printToFile(std::string name);

private:
  std::vector<Trip> _trips;
};
