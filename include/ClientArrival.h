#pragma once

#include "Client.h"
#include "Event.h"
#include "Floor.h"

class ClientArrival : public Event
{
public:
  ClientArrival(const float, const Client&);
  const Client& getClient() const;
  const Floor& getDestination() const;

private:
  const Client& client;
};
