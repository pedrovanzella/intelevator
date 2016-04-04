#pragma once

#include "CostFunction.h"
#include "DummyCostFunction.h"
#include "NNCostFunction.h"

class CostFunctionCreator
{
public:
  template <class T>
  static const std::shared_ptr<const CostFunction> create();
};

template <class T>
const std::shared_ptr<const CostFunction> CostFunctionCreator::create()
{
  const std::shared_ptr<const CostFunction> cf(new T());
  return cf;
}