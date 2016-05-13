#pragma once

#include <glog/logging.h>
#include <memory>
#include <random>
#include <string>

class Clock;
class EventQueue;
class Floor;
class Scenario;

class EventFactory
{
public:
  EventFactory(std::shared_ptr<Clock> clock, std::shared_ptr<Floor> floor, std::shared_ptr<const Scenario> scenario);
  virtual ~EventFactory();

  void createFutureArrival(const std::shared_ptr<EventQueue> eventQueue);

private:
  std::shared_ptr<Clock> _clock;
  std::shared_ptr<Floor> _floor;
  std::shared_ptr<const Scenario> _scenario;
  std::poisson_distribution<int> _distribution;
  std::seed_seq _seed_seq;
  std::default_random_engine _generator;
  int _totalArrived;
};
