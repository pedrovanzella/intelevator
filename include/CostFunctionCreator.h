#pragma once

#include "CostFunction.h"
#include "CostFunctionType.h"
#include "DummyCostFunction.h"
#include "NearestNeighbourCostFunction.h"
#include <memory>

class CostFunctionCreator {
public:
  template <class T> static const std::shared_ptr<const CostFunction> create();

  static const std::shared_ptr<const CostFunction> create(const CostFunctionType costFunctionType);
};

template <class T> const std::shared_ptr<const CostFunction> CostFunctionCreator::create() {
  const std::shared_ptr<const CostFunction> cf(new T());
  return cf;
}

const std::shared_ptr<const CostFunction> CostFunctionCreator::create(const CostFunctionType costFunctionType) {
  switch (costFunctionType) {
  case CostFunctionType::Dummy:
    return CostFunctionCreator::create<DummyCostFunction>();
  case CostFunctionType::NearestNeighbour:
    return CostFunctionCreator::create<NearestNeighbourCostFunction>();
  default:
    throw MissingCostFunctionError(std::to_string((int)costFunctionType));
  }
}