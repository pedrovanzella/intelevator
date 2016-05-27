#pragma once

#include "MissingSchedulerError.h"

enum class SchedulerType : int {
  Simple,
  Planning
};

namespace Helpers {
  static std::string schedulerName(SchedulerType type) {
    switch (type) {
    case SchedulerType::Simple:
      return "Simple";
    case SchedulerType::Planning:
      return "Planning";
    default:
      throw MissingSchedulerError(std::to_string((int)type));
    }
  }
}