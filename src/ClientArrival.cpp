#include "ClientArrival.h"
#include "EventType.h"

ClientArrival::ClientArrival(const unsigned long eventTime,
                             const std::shared_ptr<const Client> client,
                             const std::shared_ptr<const Floor> floor)
  : Event(eventTime, EventType::clientArrival)
  , _client(client)
  , _floor(floor)
{
  LOG(DEBUG) << "Created ClientArrival event with eventTime=" << _eventTime << " at floor " << floor->getNumber() << ".";
}

const std::shared_ptr<const Client> ClientArrival::getClient() const
{
  return _client;
}

const std::shared_ptr<const Floor> ClientArrival::getFloor() const
{
    return _floor;
}