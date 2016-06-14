#pragma once

#include "Event.h"
#include <memory>

class Client; // forward declaration

class ClientArrival : public Event {
public:
  ClientArrival(const unsigned long eventTime,
                const std::shared_ptr<Client> client);

  const std::shared_ptr<Client> getClient() const;
  std::string str() const;

private:
  const std::shared_ptr<Client> _client;
};
