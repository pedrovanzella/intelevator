#include "Statistics.h"
#include <ctime>
#include <cstdlib>
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
  std::time_t now = std::time(NULL);
  std::tm* ptm = std::localtime(&now);
  char buffer[32];
  std::strftime(buffer, 32, "%Y%m%d_%H%M%S", ptm);

  std::string path = "output/" + name + "_" + buffer;
  std::string filepath = path + "/run.log";
  LOG(INFO) << "Writing statistics to '" << filepath << "'.";

  std::string command = "mkdir -p " + path;
  system(command.c_str());

  std::ofstream f;
  f.open(filepath);
  for (auto t: _trips) {
    t.printToFile(f);
  }
}
