#pragma once

#include "Client.h"
#include "Elevator.h"
#include "Floor.h"
#include <memory>

class Trip {
public:
  std::shared_ptr<const Client> client;
  std::shared_ptr<const Floor> origin;
  std::shared_ptr<const Elevator> elevator;
  float waitingTime;
  float journeyTime;
  float arrivalTime;

  Trip();
};