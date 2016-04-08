#pragma once

enum class Status {
  Moving, Stopped
};

namespace Helpers
{
  static std::string statusName(Status type)
  {
    switch(type)
    {
      case Status::Moving:  return "moving";
      case Status::Stopped: return "stopped";
      default:
        throw std::invalid_argument("");
    }
  }
}