#pragma once

#include <stdexcept>

enum class EventType {
  clientArrival,
  elevatorArrival,
  cycleElevators
};

namespace Helpers
{
  static std::string eventTypeName(EventType type)
  {
    switch(type)
    {
      case EventType::clientArrival:   return "ClientArrival";
      case EventType::elevatorArrival: return "ElevatorArrival";
      case EventType::cycleElevators:  return "CycleElevators";
      default:
        throw std::invalid_argument("");
    }
  }
}