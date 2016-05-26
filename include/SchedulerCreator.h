#pragma once

#include "BetterNearestNeighbourScheduler.h"
#include "Scheduler.h"
#include "SchedulerType.h"
#include "DummyScheduler.h"
#include "NearestNeighbourScheduler.h"
#include "RandomScheduler.h"

class DispatcherCreator {
public:
  template <class T> static const std::shared_ptr<Scheduler> create();

  static const std::shared_ptr<Scheduler> create(const DispatcherType dispatcherType);
};

template <class T> const std::shared_ptr<Scheduler> DispatcherCreator::create() {
  const std::shared_ptr<Scheduler> d(new T());
  return d;
}

const std::shared_ptr<Scheduler> DispatcherCreator::create(const DispatcherType dispatcherType) {
  switch (dispatcherType) {
  case DispatcherType::Dummy:
    return DispatcherCreator::create<DummyDispatcher>();
  case DispatcherType::Random:
    return DispatcherCreator::create<RandomDispatcher>();
  case DispatcherType::NearestNeighbour:
    return DispatcherCreator::create<NearestNeighbourDispatcher>();
  case DispatcherType::BetterNearestNeighbour:
    return DispatcherCreator::create<BetterNearestNeighbourDispatcher>();
  default:
    throw MissingDispatcherError(std::to_string((int)dispatcherType));
  }
}