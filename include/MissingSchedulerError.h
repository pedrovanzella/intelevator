#pragma once
#include <stdexcept>

class MissingSchedulerError : public std::runtime_error {
public:
  explicit MissingSchedulerError(const std::string &what)
      : std::runtime_error("Scheduler not found: " + what) {}
  virtual ~MissingSchedulerError() {}
};