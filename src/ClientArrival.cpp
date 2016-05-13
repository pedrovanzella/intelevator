#include "ClientArrival.h"
#include "EventType.h"
#include <sstream>
#include <string>

ClientArrival::ClientArrival(const unsigned long eventTime,
                             const std::shared_ptr<Client> client)
    : Event(eventTime, EventType::clientArrival), _client(client) {}

const std::shared_ptr<Client> ClientArrival::getClient() const {
  return _client;
}

std::string ClientArrival::str() const {
  std::ostringstream stream;
  stream << "Client arrived at floor " << _client->getArrivalFloor()
         << " bound to " << _client->getDestination()
         << ", with size " << _client->getPartySize()
         << " (t=" << _eventTime << ").";
  return stream.str();
}