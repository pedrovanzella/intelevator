#pragma once
#include <stdexcept>

class MissingDispatcherError : public std::runtime_error {
public:
  explicit MissingDispatcherError(const std::string &what)
      : std::runtime_error("Dispatcher not found: " + what) {}
  virtual ~MissingDispatcherError() {}
};