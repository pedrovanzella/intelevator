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

  std::map<unsigned long, double> getProbabilities(const std::string seed,
                                                   const unsigned long experiments,
                                                   const double lambda) const;

  std::map<unsigned long, double> getDestProbabilities(const std::string seed,
                                                       const unsigned long experiments,
                                                       const int floors,
                                                       const int floor_number) const;

  std::map<unsigned long, unsigned long> getClients(std::map<unsigned long, double> probabilities,
                                                    const unsigned long population) const;
};
