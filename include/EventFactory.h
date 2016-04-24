#pragma once

#include "EventQueue.h"
#include <glog/logging.h>
#include <memory>
#include <random>
#include <string>

class Clock;
class Floor;

class EventFactory
{
public:
  EventFactory(std::shared_ptr<Clock> clock, std::shared_ptr<Floor> floor, std::string seed);
  virtual ~EventFactory();

  void createFutureArrival(const std::shared_ptr<EventQueue> eventQueue);

private:
  std::shared_ptr<Clock> _clock;
  std::shared_ptr<Floor> _floor;
  std::seed_seq _seed;
  std::default_random_engine _generator;
  std::poisson_distribution<int> _distribution;
};
