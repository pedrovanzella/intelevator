#include "EventFactory.h"

#include "ClientArrival.h"
#include "ElevatorArrival.h"
#include <random>

EventFactory::EventFactory(const std::shared_ptr<const Config> config,
                           const std::shared_ptr<Building> building,
                           const std::shared_ptr<EventQueue> eventQueue)
  : _config(config)
  , _building(building)
  , _eventQueue(eventQueue)
{
  LOG(TRACE) << "EventFactory created.";
}

EventFactory::~EventFactory()
{
  LOG(TRACE) << "EventFactory destroyed.";
}

std::map<unsigned long, double> EventFactory::generateEventRatios() const
{
  const std::string  seed_str            = _config->getString(Property::PoissonSeed);
  const unsigned int totalSimulationTime = _config->getInt(Property::Duration);
  const unsigned int timeBetweenEvents   = _config->getInt(Property::EventInterval);
  const unsigned int experiments         = _config->getInt(Property::Experiments);

  const float lambda = totalSimulationTime / timeBetweenEvents;
  std::seed_seq seed_sequence (seed_str.begin(), seed_str.end());
  std::default_random_engine generator(seed_sequence);
  std::poisson_distribution<int> distribution(lambda);

  std::map<unsigned long, unsigned long> events;
  for (int k = 0; k < experiments; ++k)
  {
    int event = distribution(generator);
    ++events[event];
  }

  std::map<unsigned long, double> eventRatios;
  for (auto ev : events)
  {
    eventRatios[ev.first] = 1.f * ev.second / experiments;
  }

  return eventRatios;
}

std::map<unsigned long, unsigned long> EventFactory::generateClientsPerEvent(std::map<unsigned long, double> eventRatios) const
{
  const unsigned int population  = _config->getInt(Property::Population);
  unsigned int available = population;

  std::map<unsigned long, unsigned long> clientsPerEvent;
  for (auto event : eventRatios)
  {
    unsigned int amount = ceil(event.second * population);
    if (amount > available) amount = available;
    clientsPerEvent[event.first] = amount;
    available -= amount;
  }

  return clientsPerEvent;
}

void EventFactory::initialize() const
{
  auto eventRatios = generateEventRatios();
  auto clientsPerEvent = generateClientsPerEvent(eventRatios);

  // lógica mandrakiana comentada logo abaixo :) amanhã eu adapto :)

// #include <iostream>
// #include <random>
// #include <array>

// int main()
// {

//   for (int clients = 100; clients < 105; clients++)

//   {const int experiments = 10000; // number of experiments
//     // const int clients = 139;   // maximum number of stars to distribute
  
//     const int floors = 10;
//     const int current_floor = 6;
  
//     std::array<float, floors> init;
  
//     for (int i = 0; i < floors; i++)
//     {
//       init[i] = i == current_floor ? 0 : 1;
//     }
  
//     std::default_random_engine generator;
//     std::discrete_distribution<int> distribution (init.begin(), init.end());
  
//     int p[10]={};
  
//     for (int i=0; i<experiments; ++i) {
//       int number = distribution(generator);
//       ++p[number];
//     }
  
//     // std::cout << "a discrete_distribution:" << std::endl;
//     int total = 0;
//     int available = clients;
//     for (int i=0; i<10; ++i)
//     {
//       int xxx = ceil(p[i] * clients*1.0/experiments);
//       if (xxx > available) xxx = available;
//       //if (i == 9 && available > 0) xxx += available;
  
//       std::cout << xxx << " clients of " << clients << " are going from floor " << current_floor << " to " << i << std::endl;
//       total += xxx;
//       available -= xxx;
//     }
  
//     if (clients != total)
//       std::cout << clients << " --- total: " << total << std::endl;}

//   return 0;
// }
}
