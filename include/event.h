#pragma once

#include "eventtype.h"
#include "client.h"
#include "elevator.h"
#include "floor.h"

class Event {
public:
  EventType eventType;
  float eventTime;
  std::shared_ptr<Client> client;
  std::shared_ptr<Elevator> elevator;
  std::shared_ptr<Floor> floor;

  Event(EventType type, float time) : eventType(type), eventTime(time) {}
};