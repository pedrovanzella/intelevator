#pragma once

#include "BetterNearestNeighbourDispatcher.h"
#include "Dispatcher.h"
#include "DummyDispatcher.h"
#include "NearestNeighbourDispatcher.h"

class DispatcherCreator
{
public:
  template <class T>
  static const std::shared_ptr<Dispatcher> create();
};

template <class T>
const std::shared_ptr<Dispatcher> DispatcherCreator::create()
{
  const std::shared_ptr<Dispatcher> d(new T());
  return d;
}
