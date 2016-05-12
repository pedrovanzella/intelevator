#pragma once

#include "Event.h"
#include <glog/logging.h>

class FinishSimulation : public Event {
public:
  FinishSimulation(const unsigned long eventTime);

  std::string str() const;
};
