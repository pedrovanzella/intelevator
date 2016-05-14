#pragma once

#include "MissingCostFunctionError.h"

enum class CostFunctionType { Dummy, NearestNeighbour };

namespace Helpers {
  static std::string costFunctionName(CostFunctionType type) {
    switch (type) {
    case CostFunctionType::Dummy:
      return "Dummy";
    case CostFunctionType::NearestNeighbour:
      return "NearestNeighbour";
    default:
      throw MissingCostFunctionError(std::to_string((int)type));
    }
  }
}