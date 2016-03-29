#pragma once
#include <stdexcept>

class MissingCostFunctionError : public std::runtime_error
{
public:
  explicit MissingCostFunctionError(const std::string& what) : std::runtime_error("Cost Function not found: " + what) {}
  virtual ~MissingCostFunctionError() {}
};
