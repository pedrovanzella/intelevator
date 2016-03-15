#include <gtest/gtest.h>

#include "Elevator.h"

struct ElevatorTest : testing::Test
{
  Config config;
  Elevator* elevator;

  ElevatorTest()
  {
    config._maxLoad = 10;
    elevator = new Elevator(config);
  }

  virtual ~ElevatorTest()
  {
    delete elevator;
  }
};

TEST_F(ElevatorTest, NoPassengers_ReturnsOccupation_Zero)
{
  EXPECT_EQ(elevator->getOccupation(), 0.0);
}
