#pragma once
#include "MissingDispatcherError.h"

enum class DispatcherType : int
{
  Dummy,
  NearestNeighbour,
  BetterNearestNeighbour
};

namespace Helpers
{
  static std::string dispatcherName(DispatcherType type)
  {
    switch(type)
    {
      case DispatcherType::Dummy: return "Dummy";
      case DispatcherType::NearestNeighbour: return "NearestNeighbour";
      case DispatcherType::BetterNearestNeighbour: return "BetterNearestNeighbour";
      default:
        throw MissingDispatcherError(std::to_string((int)type));
    }
  }
}