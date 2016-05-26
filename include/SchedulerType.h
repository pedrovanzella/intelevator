#pragma once

#include "MissingSchedulerError.h"

enum class SchedulerType : int {
  Dummy,
  Random,
  NearestNeighbour,
  BetterNearestNeighbour
};

namespace Helpers {
  static std::string schedulerName(SchedulerType type) {
    switch (type) {
    case SchedulerType::Dummy:
      return "Dummy";
    case SchedulerType::Random:
      return "Random";
    case SchedulerType::NearestNeighbour:
      return "NearestNeighbour";
    case SchedulerType::BetterNearestNeighbour:
      return "BetterNearestNeighbour";
    default:
      throw MissingSchedulerError(std::to_string((int)type));
    }
  }
}