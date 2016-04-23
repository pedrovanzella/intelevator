#pragma once

#include <glog/logging.h>
#include <memory>

class Simulator; // forward-declaration

class EventFactory
{
public:
  EventFactory(std::shared_ptr<Simulator> simulator);
  virtual ~EventFactory();

  static std::shared_ptr<std::vector<std::shared_ptr<EventFactory>>> create(std::shared_ptr<Simulator> simulator);

private:
  std::shared_ptr<Simulator> _simulator;
};
