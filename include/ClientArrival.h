#pragma once

#include "Client.h"
#include "Event.h"
#include "Floor.h"
#include <glog/logging.h>
#include <memory>

class ClientArrival : public Event {
public:
  ClientArrival(const unsigned long eventTime,
                const std::shared_ptr<Client> client);

  const std::shared_ptr<Client> getClient() const;

private:
  const std::shared_ptr<Client> _client;
};
