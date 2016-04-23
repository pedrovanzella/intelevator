#pragma once

#include <glog/logging.h>
#include <random>

class EventFactory
{
public:
  EventFactory(const std::string seed);
  virtual ~EventFactory();

private:
  std::seed_seq _seed_sequence;
};
