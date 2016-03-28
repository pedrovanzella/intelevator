#include "EventFactory.h"

#include "ClientArrival.h"
#include "ElevatorArrival.h"

EventFactory::EventFactory(const std::shared_ptr<Building> building, const std::shared_ptr<Clock> clock)
  : _building(building)
  , _clock(clock)
{
  LOG(TRACE) << "EventFactory created.";
}

EventFactory::~EventFactory()
{
  LOG(TRACE) << "EventFactory destroyed.";
}

const std::shared_ptr<const Event> EventFactory::createEvent(EventType eventType) const
{
  switch(eventType)
  {
    case EventType::clientArrival:
    {
      auto eventLocation = _building->getFloors().front();
      auto destination = _building->getFloors().front();
      std::shared_ptr<Client> client(new Client(1, _clock->currentTime(), destination));
      std::shared_ptr<const Event> ev(new ClientArrival(_clock->currentTime(), client, eventLocation));
      return ev;
    }
    case EventType::elevatorArrival:
    {
      auto eventLocation = _building->getFloors().front();
      auto elevator = _building->getElevators().front();
      std::shared_ptr<const Event> ev(new ElevatorArrival(_clock->currentTime(), elevator, eventLocation));
      return ev;
    }
    default:
      throw std::invalid_argument("Invalid event type.");
  }
}