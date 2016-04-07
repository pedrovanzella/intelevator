#include <gtest/gtest.h>

#include "Elevator.h"
#include "Floor.h"

struct ElevatorTest : testing::Test
{
  int number;
  int capacity;
  int floor;
  std::shared_ptr<const Elevator> elevator;

  ElevatorTest()
  : number(0)
  , capacity(8)
  , floor(0)
  , elevator(new Elevator(number, capacity, floor))
  {}

  virtual ~ElevatorTest()
  {}
};

TEST_F(ElevatorTest, NoPassengers_ReturnsOccupation_Zero)
{
  EXPECT_EQ(elevator->getAvailableCapacity(), capacity);
}

TEST_F(ElevatorTest, GetNumber)
{
  EXPECT_EQ(elevator->getNumber(), number);
}

TEST_F(ElevatorTest, GetCapacity)
{
  EXPECT_EQ(elevator->getCapacity(), capacity);
}

TEST_F(ElevatorTest, GetLocation)
{
  EXPECT_EQ(elevator->getLocation(), floor);
}
