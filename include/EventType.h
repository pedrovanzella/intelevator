#pragma once

#include <stdexcept>
#include <string>

enum class EventType {
  clientArrival,
  finishSimulation
};

namespace Helpers
{
  static std::string eventTypeName(EventType type)
  {
    switch(type)
    {
      case EventType::clientArrival:   return "ClientArrival";
      case EventType::finishSimulation: return "FinishSimulation";
      default:
        throw std::invalid_argument("");
    }
  }
}