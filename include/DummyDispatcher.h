#pragma once

#include <memory>
#include "Building.h"
#include "ClientArrival.h"
#include "Dispatcher.h"
#include "Elevator.h"

class DummyDispatcher : public Dispatcher
{
public:
  explicit DummyDispatcher(std::shared_ptr<Building> building): Dispatcher(building) {}

  std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const;
};
