#pragma once

#include "CostFunction.h"
#include "CostFunctionType.h"
#include "DummyCostFunction.h"
#include "NearestNeighbourCostFunction.h"
#include "WeightedCostFunction.h"
#include <memory>

class CostFunctionCreator {
public:
  template <class T> static const std::shared_ptr<CostFunction> create();

  static const std::shared_ptr<CostFunction> create(const CostFunctionType costFunctionType);
};

template <class T> const std::shared_ptr<CostFunction> CostFunctionCreator::create() {
  const std::shared_ptr<CostFunction> cf(new T());
  return cf;
}

const std::shared_ptr<CostFunction> CostFunctionCreator::create(const CostFunctionType costFunctionType) {
  switch (costFunctionType) {
  case CostFunctionType::Dummy:
    return CostFunctionCreator::create<DummyCostFunction>();
  case CostFunctionType::NearestNeighbour:
    return CostFunctionCreator::create<NearestNeighbourCostFunction>();
  case CostFunctionType::Weighted:
    return CostFunctionCreator::create<WeightedCostFunction>();
  default:
    throw MissingCostFunctionError(std::to_string((int)costFunctionType));
  }
}
