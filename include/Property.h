#pragma once

#include <string>

enum class Property
{
  // Simulation properties
  Title,
  Duration,

  // Building properties
  Floors,
  Elevators,
  MaxLoad,

  // Dispatcher properties
  Dispatcher,
  CostFunction,

  // Poisson process properties
  PoissonSeed,
  Population,
  EventInterval,
  Experiments,
};