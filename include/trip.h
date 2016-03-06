#ifndef _TRIP_H_
#define _TRIP_H_

#include "client.h"
#include "floor.h"
#include "elevator.h"

class Trip {
public:
  std::shared_ptr<Client> client;
  std::shared_ptr<Floor> origin;
  std::shared_ptr<Elevator> elevator;
  float waitingTime;
  float journeyTime;
  float arrivalTime;
};

#endif /* _TRIP_H_ */
