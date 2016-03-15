#pragma once

#include "Client.h"
#include "Elevator.h"
#include "Floor.h"

class Trip {
public:
  Client* _client;
  Floor* _origin;
  Elevator* _elevator;
  float _waitingTime;
  float _journeyTime;
  float _arrivalTime;

  Trip();
};