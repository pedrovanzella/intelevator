#include "FinishSimulation.h"
#include "EventType.h"

FinishSimulation::FinishSimulation(const unsigned long eventTime)
  : Event(eventTime, EventType::finishSimulation) {}