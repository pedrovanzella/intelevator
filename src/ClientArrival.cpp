#include "ClientArrival.h"
#include "EventType.h"

ClientArrival::ClientArrival(const float eventTime, const std::shared_ptr<const Client> client)
 : Event(eventTime, EventType::clientArrival)
 , _client(client) {}

const std::shared_ptr<const Client> ClientArrival::getClient() const
{
  return _client;
}
