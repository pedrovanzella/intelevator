#include "ClientArrival.h"
#include "EventType.h"

ClientArrival::ClientArrival(const float eventTime, const Client& client)
 : Event(eventTime, EventType::clientArrival)
 , _client(client) {}

const Client& ClientArrival::getClient() const
{
  return _client;
}

const Floor& ClientArrival::getDestination() const
{
  return _client._destination;
}
