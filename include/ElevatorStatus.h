#pragma once

enum class ElevatorStatus {
  Moving, Stopped
};

namespace Helpers
{
  static std::string elevatorStatusName(ElevatorStatus type)
  {
    switch(type)
    {
      case ElevatorStatus::Moving:  return "moving";
      case ElevatorStatus::Stopped: return "stopped";
      default:
        throw std::invalid_argument("");
    }
  }
}