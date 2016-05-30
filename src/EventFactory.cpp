#include "EventFactory.h"
#include "Client.h"
#include "ClientArrival.h"
#include "Clock.h"
#include "EventQueue.h"
#include "Floor.h"
#include "Scenario.h"

EventFactory::EventFactory(std::shared_ptr<Clock> clock,
                           std::shared_ptr<Floor> floor,
                           std::shared_ptr<const Scenario> scenario,
                           std::shared_ptr<std::default_random_engine> random_engine)
  : _clock(clock), _floor(floor), _scenario(scenario),
    _arrival_distribution(floor->getLambda()), _random_engine(random_engine),
    _totalArrived(0) {

  std::vector<float> probabilities(_scenario->getFloorCount(), 1.f);
  probabilities[_floor->getNumber()] = 0.f;
  _destination_distribution = std::discrete_distribution<int>(probabilities.begin(), probabilities.end());
}

EventFactory::~EventFactory() {}

void EventFactory::createFutureArrival(const std::shared_ptr<EventQueue> eventQueue) {
  // if (_totalArrived >= _floor->getPopulation()) return;

  auto partySize = 1u;
  auto eventTime = _clock->currentTime() + getNextTime();
  auto destination = getNextDestination();

  auto client = std::make_shared<Client>(partySize, _floor->getNumber(), destination, eventTime);
  auto ca = std::make_shared<ClientArrival>(eventTime, client);
  eventQueue->push(std::static_pointer_cast<Event>(ca));

  _totalArrived += partySize;
}

int EventFactory::getNextTime() {
  return _arrival_distribution(*_random_engine);
}

int EventFactory::getNextDestination() {
  return _destination_distribution(*_random_engine);
}