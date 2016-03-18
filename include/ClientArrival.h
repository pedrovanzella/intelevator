#pragma once

#include <memory>
#include "Client.h"
#include "Event.h"
#include "Floor.h"

class ClientArrival : public Event
{
public:
  ClientArrival(const float eventTime, const std::shared_ptr<const Client> client);
  const std::shared_ptr<const Client> getClient() const;

private:
  const std::shared_ptr<const Client> _client;
};
