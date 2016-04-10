#pragma once

#include "Client.h"
#include "Elevator.h"
#include "Floor.h"
#include <memory>

class Trip {
public:
  std::shared_ptr<Client> _client;
  std::shared_ptr<const Floor> _origin;
  std::shared_ptr<const Elevator> _elevator;
  float _waitingTime;
  float _journeyTime;
  float _arrivalTime;

  Trip();
};