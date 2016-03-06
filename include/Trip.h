#pragma once

#include "Client.h"
#include "Elevator.h"
#include "Floor.h"

class Trip {
public:
  Client* client;
  Floor* origin;
  Elevator* elevator;
  float waitingTime;
  float journeyTime;
  float arrivalTime;

  Trip();
};