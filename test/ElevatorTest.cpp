#include <gtest/gtest.h>

#include "Elevator.h"

struct ElevatorTest : testing::Test
{
  Config config;
  Elevator* elevator;

  ElevatorTest()
  {
    config.maxLoad = 10;
    elevator = new Elevator(config);
  }

  virtual ~ElevatorTest()
  {
    delete elevator;
  }
};