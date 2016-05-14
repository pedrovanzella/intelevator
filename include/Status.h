#pragma once

#include <string>
#include <stdexcept>

enum class Status {
  Moving,  // Elevator is moving. :P
  Stopped, // Elevator is stopped in a floor but is still travelling.
  Idle     // Elevator is stopped and has nothing to do with its life.
};

namespace Helpers
{
  static std::string statusName(Status type)
  {
    switch(type)
    {
      case Status::Moving:  return "moving";
      case Status::Stopped: return "stopped";
      case Status::Idle: return "idle";
      default:
        throw std::invalid_argument("");
    }
  }
}