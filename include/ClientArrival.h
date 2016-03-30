#pragma once

#include <memory>
#include "Client.h"
#include "easylogging++.h"
#include "Event.h"
#include "Floor.h"

class ClientArrival : public Event
{
public:
  ClientArrival(const unsigned long eventTime, const std::shared_ptr<const Client> client, const std::shared_ptr<const Floor> floor);
  const std::shared_ptr<const Client> getClient() const;
  const std::shared_ptr<const Floor> getFloor() const;

private:
  const std::shared_ptr<const Client> _client;
  const std::shared_ptr<const Floor> _floor;
};
