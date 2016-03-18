#include <gtest/gtest.h>

#include "Elevator.h"

struct ElevatorTest : testing::Test
{
  std::shared_ptr<Config> config;
  std::shared_ptr<Building> building;
  std::shared_ptr<Elevator> elevator;

  ElevatorTest()
  : config(new Config())
  , building(new Building(config))
  , elevator(new Elevator(building))
  {
    config->setMaxLoad(10);
    config->setElevators(1);
  }

  virtual ~ElevatorTest()
  {
  }
};

// Elevator::getOccupation() tests

TEST_F(ElevatorTest, NullMaxLoad_ReturnsOccupation_Zero)
{
  config->setMaxLoad(0);
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}

TEST_F(ElevatorTest, NoPassengers_ReturnsOccupation_Zero)
{
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}
