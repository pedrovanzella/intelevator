#include "ClientArrival.h"
#include "Clock.h"
#include "EventFactory.h"
#include "EventQueue.h"
#include "Floor.h"
#include "Scenario.h"

EventFactory::EventFactory(std::shared_ptr<Clock> clock,
                           std::shared_ptr<Floor> floor,
                           std::shared_ptr<const Scenario> scenario)
    : _clock(clock), _floor(floor), _scenario(scenario), _distribution(floor->getLambda()), _totalArrived(0) {
      std::string seed = _scenario->getSeed();
      _seed_seq = std::seed_seq(seed.begin(), seed.end());
      _generator = std::default_random_engine(_seed_seq);
    }

EventFactory::~EventFactory() {}

void EventFactory::createFutureArrival(const std::shared_ptr<EventQueue> eventQueue) {
  if (_totalArrived >= _floor->getPopulation()) return;
  // TODO: remover esta salvaguarda...
  // Quando o sistema processa um evento onde andar origem == andar destino, EXPLODE :'(
  if (_floor->getNumber() == 5) return;

  // TODO: criar estes três valores 'aleatoriamente' e 'consumindo' a população daquele andar...
  auto partySize = 1u;
  auto eventTime = _clock->currentTime() * 2 + _floor->getNumber() + 10;
  auto destination = 5u;

  auto client = std::make_shared<Client>(partySize, _floor->getNumber(), destination, eventTime);
  auto ca = std::make_shared<ClientArrival>(eventTime, client);
  eventQueue->push(std::static_pointer_cast<Event>(ca));

  _totalArrived += partySize;
}