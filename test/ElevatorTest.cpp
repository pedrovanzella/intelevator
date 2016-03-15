#include <gtest/gtest.h>

#include "Elevator.h"

struct ElevatorTest : testing::Test
{
  Config config;
  Elevator* elevator;

  ElevatorTest()
  {
    config._maxLoad = 10;
    config._elevators = 1;
    elevator = new Elevator(config, nullptr);
  }

  virtual ~ElevatorTest()
  {
    delete elevator;
  }
};

TEST_F(ElevatorTest, NullMaxLoad_ReturnsOccupation_Zero)
{
  config._maxLoad = 0;
  elevator = new Elevator(config, nullptr);
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}

TEST_F(ElevatorTest, NoPassengers_ReturnsOccupation_Zero)
{
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}
