#include "Simulator.h"
#include "easylogging++.h"
#include <random>

Simulator::Simulator(const std::shared_ptr<const Config> config,
                     const std::shared_ptr<Building> building,
                     const std::shared_ptr<Statistics> statistics,
                     const std::shared_ptr<Clock> clock,
                     const std::shared_ptr<EventQueue> eventQueue,
                     const std::shared_ptr<EventDispatcher> eventDispatcher,
                     const std::shared_ptr<EventFactory> eventFactory)
  : _config(config)
  , _building(building)
  , _statistics(statistics)
  , _clock(clock)
  , _eventQueue(eventQueue)
  , _eventDispatcher(eventDispatcher)
  , _eventFactory(eventFactory)
{
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));
}

Simulator::~Simulator()
{
  _eventDispatcher->unsubscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->unsubscribe(std::static_pointer_cast<EventObserver>(_statistics));
  _eventDispatcher->unsubscribe(std::static_pointer_cast<EventObserver>(_clock));
}

void Simulator::run()
{
  initializeEventQueue();
  LOG(INFO) << "Simulation started.";
  while (_statistics->keepRunning() && _eventQueue->hasNextEvent())
  {
    auto e = _eventQueue->pop();
    _eventDispatcher->broadcast(e);
  }
  LOG(INFO) << "Simulation completed.";
}

void Simulator::initializeEventQueue()
{
  // isto tudo deverá ser movido para uma classe de geração de eventos...

  std::map<int, unsigned long> clientsPerEvent;

  const std::string  seed_str            = _config->getString(Property::PoissonSeed);
  const unsigned int totalSimulationTime = _config->getInt(Property::Duration);
  const unsigned int timeBetweenEvents   = _config->getInt(Property::EventInterval);
  const unsigned int experiments         = _config->getInt(Property::Experiments);
  const unsigned int population          = _config->getInt(Property::Population);

  const float lambda = totalSimulationTime / timeBetweenEvents;

  std::seed_seq seed_sequence (seed_str.begin(), seed_str.end());
  std::default_random_engine generator(seed_sequence);
  std::poisson_distribution<int> distribution(lambda);

  for (int k = 0; k < experiments; ++k)
  {
    int eventNumber = distribution(generator);
    ++clientsPerEvent[eventNumber];
  }

  auto lobby = _building->getLobby();
  auto roof = _building->getFloor(_config->getInt(Property::Floors) - 1); // manda todo mundo pro último andar por enquanto :P

  int totalClients = 0;
  float ratio = 1.f * population / experiments;
  for (auto it : clientsPerEvent)
  {
    int clientsInThisEvent = round(it.second * ratio);
    if (clientsInThisEvent <= 0) continue;

    std::shared_ptr<Client> c(new Client(clientsInThisEvent, it.first, roof));
    std::shared_ptr<ClientArrival> ca(new ClientArrival(it.first, c, lobby));

    _eventQueue->push(std::static_pointer_cast<Event>(ca));

    LOG(DEBUG) << "Event " << it.first << " will have " << clientsInThisEvent << " clients arriving.";

    totalClients += clientsInThisEvent;
  }

  LOG(INFO) << "Scheduled a total of " << totalClients << " clients.";
}

bool Simulator::nextStep()
{
  return true;
}

