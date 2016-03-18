#pragma once

#include "Client.h"
#include "Event.h"
#include "Floor.h"

class ClientArrival : public Event
{
public:
  ClientArrival(const float eventTime, const Client& client);
  const Client& getClient() const;

private:
  const Client& _client;
};
