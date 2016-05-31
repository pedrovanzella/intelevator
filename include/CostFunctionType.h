#pragma once

#include "MissingCostFunctionError.h"
#include <string>

enum class CostFunctionType { Dummy, Random, NearestNeighbour, BetterNearestNeighbour, Weighted };

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
namespace Helpers {
  static std::string costFunctionName(CostFunctionType type) {
    switch (type) {
    case CostFunctionType::Dummy:
      return "Dummy";
    case CostFunctionType::Random:
      return "Random";
    case CostFunctionType::NearestNeighbour:
      return "NearestNeighbour";
    case CostFunctionType::BetterNearestNeighbour:
      return "BetterNearestNeighbour";
    case CostFunctionType::Weighted:
      return "Weighted";
    default:
      throw MissingCostFunctionError(std::to_string((int)type));
    }
  }
}
#pragma clang diagnostic pop