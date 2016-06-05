#pragma once

#include "MissingSchedulerError.h"

enum class SchedulerType : int {
  Simple,
  Planning,
  Sayajin
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
namespace Helpers {
  static std::string schedulerName(SchedulerType type) {
    switch (type) {
    case SchedulerType::Simple:
      return "Simple";
    case SchedulerType::Planning:
      return "Planning";
    case SchedulerType::Sayajin:
      return "Sayajin";
    default:
      throw MissingSchedulerError(std::to_string((int)type));
    }
  }
}
#pragma clang diagnostic pop
