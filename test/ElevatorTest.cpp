#include <gtest/gtest.h>

#include "Elevator.h"

struct ElevatorTest : testing::Test
{
  std::shared_ptr<Config> config;
  std::shared_ptr<Building> building;
  std::shared_ptr<const Elevator> elevator;

  ElevatorTest()
  : config(new Config("test_config.yaml"))
  , building(new Building(config))
  {
    building->initialize();
    elevator = building->getElevator(0);
  }

  virtual ~ElevatorTest()
  {}
};

// Elevator::getOccupation() tests
TEST_F(ElevatorTest, NullMaxLoad_ReturnsOccupation_Zero)
{
  config->setInt(Property::MaxLoad, 0);
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}

TEST_F(ElevatorTest, NoPassengers_ReturnsOccupation_Zero)
{
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}