#pragma once

#include <stdexcept>
#include <string>

enum class Direction { Up, Down, None };

namespace Helpers {
  static std::string directionName(Direction type) {
    switch (type) {
    case Direction::Up:
      return "Up";
    case Direction::Down:
      return "Down";
    case Direction::None:
      return "None";
    default:
      throw std::invalid_argument("");
    }
  }
}