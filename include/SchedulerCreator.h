#pragma once

#include "BetterNearestNeighbourScheduler.h"
#include "DummyScheduler.h"
#include "NearestNeighbourScheduler.h"
#include "PlanningScheduler.h"
#include "RandomScheduler.h"
#include "Scheduler.h"
#include "SchedulerType.h"

class SchedulerCreator {
public:
  template <class T> static const std::shared_ptr<Scheduler> create();

  static const std::shared_ptr<Scheduler> create(const SchedulerType schedulerType);
};

template <class T> const std::shared_ptr<Scheduler> SchedulerCreator::create() {
  const std::shared_ptr<Scheduler> d(new T());
  return d;
}

const std::shared_ptr<Scheduler> SchedulerCreator::create(const SchedulerType schedulerType) {
  switch (schedulerType) {
  case SchedulerType::Dummy:
    return SchedulerCreator::create<DummyScheduler>();
  case SchedulerType::Random:
    return SchedulerCreator::create<RandomScheduler>();
  case SchedulerType::NearestNeighbour:
    return SchedulerCreator::create<NearestNeighbourScheduler>();
  case SchedulerType::BetterNearestNeighbour:
    return SchedulerCreator::create<BetterNearestNeighbourScheduler>();
  case SchedulerType::Planning:
    return SchedulerCreator::create<PlanningScheduler>();
  default:
    throw MissingSchedulerError(std::to_string((int)schedulerType));
  }
}