#include "Statistics.h"
#include <glog/logging.h>

Statistics::Statistics() {}

Statistics::~Statistics() {}

bool Statistics::keepRunning() const { return true; }

void Statistics::notify(const std::shared_ptr<const Event> event) {
  // Handle events
}

void Statistics::addTrip(const unsigned long dropOffTime,
                         const std::shared_ptr<Elevator> elevator,
                         const std::shared_ptr<Client> passenger) {
  auto t = Trip();
  t.elevatorID = elevator->getNumber();
  t.partySize = passenger->getPartySize();
  t.dropOffFloor = elevator->getLocation();
  t.arrivalFloor = passenger->getArrivalFloor();
  t.dropoffTime = dropOffTime;
  t.pickupTime = passenger->getPickupTime();
  t.createTime = passenger->getCreateTime();
  t.clientID = passenger->getId();
  _trips.push_back(t);
}

void Statistics::printToFile(std::string name)
{
  std::ofstream f;
  f.open(name);

  for (auto t: _trips) {
    t.printToFile(f);
  }
}
