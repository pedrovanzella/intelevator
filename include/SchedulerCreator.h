#pragma once

#include "PlanningScheduler.h"
#include "SayajinScheduler.h"
#include "Scheduler.h"
#include "SchedulerType.h"
#include "SimpleScheduler.h"

class SchedulerCreator {
public:
  template <class T> static const std::shared_ptr<Scheduler> create();

  static const std::shared_ptr<Scheduler>
  create(const SchedulerType schedulerType);
};

template <class T> const std::shared_ptr<Scheduler> SchedulerCreator::create() {
  const std::shared_ptr<Scheduler> d(new T());
  return d;
}

const std::shared_ptr<Scheduler>
SchedulerCreator::create(const SchedulerType schedulerType) {
  switch (schedulerType) {
  case SchedulerType::Simple:
    return SchedulerCreator::create<SimpleScheduler>();
  case SchedulerType::Planning:
    return SchedulerCreator::create<PlanningScheduler>();
  case SchedulerType::Sayajin:
    return SchedulerCreator::create<SayajinScheduler>();
  default:
    throw MissingSchedulerError(std::to_string((int)schedulerType));
  }
}