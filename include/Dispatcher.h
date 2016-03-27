#pragma once

#include <memory>
#include "ClientArrival.h"

class Building; // forward declaration
class Elevator; // forward declaration

class Dispatcher : public std::enable_shared_from_this<Dispatcher>
{
public:
  Dispatcher(std::shared_ptr<Building> building);
  virtual ~Dispatcher() {}

  virtual std::shared_ptr<const Elevator> pick_next_elevator(const std::shared_ptr<const ClientArrival>) const = 0;

protected:
  std::shared_ptr<Building> _building;
};
