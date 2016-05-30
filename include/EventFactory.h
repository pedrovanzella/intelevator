#pragma once

#include <glog/logging.h>
#include <memory>
#include <random>
#include <string>

class Clock;      // forward declaration
class EventQueue; // forward declaration
class Floor;      // forward declaration
class Scenario;   // forward declaration

class EventFactory {
public:
  EventFactory(std::shared_ptr<Clock> clock, std::shared_ptr<Floor> floor,
               std::shared_ptr<const Scenario> scenario,
               std::shared_ptr<std::mt19937> random_engine);
  virtual ~EventFactory();

  void createFutureArrival(const std::shared_ptr<EventQueue> eventQueue);

private:
  std::shared_ptr<Clock> _clock;
  std::shared_ptr<Floor> _floor;
  std::shared_ptr<const Scenario> _scenario;

  std::discrete_distribution<int> _destination_distribution;
  std::poisson_distribution<int> _arrival_distribution;

  std::shared_ptr<std::mt19937> _random_engine;

  int getNextTime();
  int getNextDestination();
};
