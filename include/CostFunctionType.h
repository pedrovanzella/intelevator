#pragma once
#include "MissingCostFunctionError.h"

enum class CostFunctionType
{
  Dummy,
  NearestNeighbour
};

namespace Helpers
{
  static std::string costFunctionName(CostFunctionType type)
  {
    std::shared_ptr<const CostFunction> costFunction;
    switch(type)
    {
      case CostFunctionType::Dummy: return "Dummy";
      case CostFunctionType::NearestNeighbour: return "NearestNeighbour";
      default:
        throw MissingCostFunctionError(std::to_string((int)type));
    }
  }
}