#pragma once

#include "Client.h"
#include "Elevator.h"
#include "EventType.h"
#include "Floor.h"

class Event {
public:
  EventType eventType;
  float eventTime;
  Client* client;
  Elevator* elevator;
  Floor* floor;

  Event(EventType, float);
};