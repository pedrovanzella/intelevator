#pragma once

#include "Event.h"

class FinishSimulation : public Event {
public:
  FinishSimulation(const unsigned long eventTime);

  std::string str() const;
};
