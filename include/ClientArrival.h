#pragma once

#include <memory>
#include "Client.h"
#include <glog/logging.h>
#include "Event.h"
#include "Floor.h"

class ClientArrival : public Event
{
public:
  ClientArrival(const unsigned long eventTime, const std::shared_ptr<const Client> client, int location);
  const std::shared_ptr<const Client> getClient() const;
  int getLocation() const;

private:
  const std::shared_ptr<const Client> _client;
  int _location;
};
