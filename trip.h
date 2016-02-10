#ifndef _TRIP_H_
#define _TRIP_H_

#include "client.h"
#include "floor.h"
#include "elevator.h"

class Trip {
public:
  Client client;
  Floor origin;
  Elevator elevator;
  float waitingTime;
  float journeyTime;
  float arrivalTime;
};

#endif /* _TRIP_H_ */
