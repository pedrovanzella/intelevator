#pragma once

#include "BetterNearestNeighbourDispatcher.h"
#include "Dispatcher.h"
#include "DispatcherType.h"
#include "DummyDispatcher.h"
#include "NearestNeighbourDispatcher.h"
#include "RandomDispatcher.h"

class DispatcherCreator {
public:
  template <class T> static const std::shared_ptr<Dispatcher> create();

  static const std::shared_ptr<Dispatcher> create(const DispatcherType dispatcherType);
};

template <class T> const std::shared_ptr<Dispatcher> DispatcherCreator::create() {
  const std::shared_ptr<Dispatcher> d(new T());
  return d;
}

const std::shared_ptr<Dispatcher> DispatcherCreator::create(const DispatcherType dispatcherType) {
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