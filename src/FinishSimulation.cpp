#include "FinishSimulation.h"
#include "EventType.h"
#include <sstream>
#include <string>

FinishSimulation::FinishSimulation(const unsigned long eventTime)
  : Event(eventTime, EventType::finishSimulation) {}

std::string FinishSimulation::str() const {
  std::ostringstream stream;
  stream << "Simulation reached specified duration (t=" << _time << ").";
  return stream.str();
}