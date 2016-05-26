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

  static const std::shared_ptr<Scheduler> create(const SchedulerType schedulerType);
};

template <class T> const std::shared_ptr<Scheduler> DispatcherCreator::create() {
  const std::shared_ptr<Scheduler> d(new T());
  return d;
}

const std::shared_ptr<Scheduler> DispatcherCreator::create(const SchedulerType schedulerType) {
  switch (schedulerType) {
  case SchedulerType::Dummy:
    return DispatcherCreator::create<DummyScheduler>();
  case SchedulerType::Random:
    return DispatcherCreator::create<RandomScheduler>();
  case SchedulerType::NearestNeighbour:
    return DispatcherCreator::create<NearestNeighbourScheduler>();
  case SchedulerType::BetterNearestNeighbour:
    return DispatcherCreator::create<BetterNearestNeighbourScheduler>();
  default:
    throw MissingSchedulerError(std::to_string((int)schedulerType));
  }
}