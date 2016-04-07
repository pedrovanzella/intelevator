#include "ClientArrival.h"
#include "EventType.h"

ClientArrival::ClientArrival(const unsigned long eventTime,
                             const std::shared_ptr<const Client> client,
                             int location)
  : Event(eventTime, EventType::clientArrival)
  , _client(client)
  , _location(location)
{}

const std::shared_ptr<const Client> ClientArrival::getClient() const
{
  return _client;
}

int ClientArrival::getLocation() const
{
    return _location;
}