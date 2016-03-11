#include "ClientArrival.h"
#include "EventType.h"

ClientArrival::ClientArrival(const float eventTime, const Client& client)
 : Event(eventTime, EventType::clientArrival)
 , client(client) {}

const Client& ClientArrival::getClient() const
{
  return this->client;
}

const Floor& ClientArrival::getDestination() const
{
  return this->client.destination;
}
