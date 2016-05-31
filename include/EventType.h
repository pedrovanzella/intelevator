#pragma once

#include <stdexcept>
#include <string>

enum class EventType { clientArrival, finishSimulation };

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
namespace Helpers {
  static std::string eventTypeName(EventType type) {
    switch (type) {
    case EventType::clientArrival:
      return "ClientArrival";
    case EventType::finishSimulation:
      return "FinishSimulation";
    default:
      throw std::invalid_argument("");
    }
  }
}
#pragma clang diagnostic pop
