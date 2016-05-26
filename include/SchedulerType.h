#pragma once

#include "MissingSchedulerError.h"

enum class SchedulerType : int {
  Dummy,
  Random,
  NearestNeighbour,
  BetterNearestNeighbour,
  Planning
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
    case SchedulerType::Planning:
      return "Planning";
    default:
      throw MissingSchedulerError(std::to_string((int)type));
    }
  }
}