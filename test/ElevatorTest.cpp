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

// Elevator::getOccupation() tests

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

// Elevator::addPassenger() tests

TEST_F(ElevatorTest, AddOnePassenger)
{
  Floor f(0);
  Client c(1, 0.0, f);

  elevator->addPassenger(c);

  EXPECT_EQ(elevator->getDestinations()->count(), 1);

  Client c2(1, 0.0, f);
  elevator->addPassenger(c2);

  EXPECT_EQ(elevator->getDestinations()->count(), 2);

  EXPECT_DOUBLE_EQ(elevator->getOccupation(), 0.2);
}
