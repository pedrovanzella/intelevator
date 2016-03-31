#pragma once

#include <memory>
#include <string>

#include "Building.h"
#include "easylogging++.h"
#include "Event.h"
#include "EventQueue.h"
#include "EventType.h"

class EventFactory
{
public:
  EventFactory(const std::shared_ptr<const Config> config,
               const std::shared_ptr<Building> building,
               const std::shared_ptr<EventQueue> eventQueue);
  virtual ~EventFactory();

  void initialize() const;

private:
  const std::shared_ptr<const Config> _config;
  const std::shared_ptr<Building> _building;
  const std::shared_ptr<EventQueue> _eventQueue;

  std::map<unsigned long, double> generateEventRatios() const;
  std::map<unsigned long, unsigned long> generateClientsPerEvent(std::map<unsigned long, double> events) const;
};
