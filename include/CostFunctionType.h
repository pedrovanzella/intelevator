#pragma once

#include "MissingCostFunctionError.h"
#include <string>

enum class CostFunctionType { Dummy, NearestNeighbour, Weighted };

namespace Helpers {
  static std::string costFunctionName(CostFunctionType type) {
    switch (type) {
    case CostFunctionType::Dummy:
      return "Dummy";
    case CostFunctionType::NearestNeighbour:
      return "NearestNeighbour";
    case CostFunctionType::Weighted:
      return "Weighted";
    default:
      throw MissingCostFunctionError(std::to_string((int)type));
    }
  }
}
