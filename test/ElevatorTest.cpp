#include <gtest/gtest.h>

#include "Elevator.h"
#include "Floor.h"

struct ElevatorTest : testing::Test
{
  int number;
  int capacity;
  std::shared_ptr<const Floor> floor;
  std::shared_ptr<const Elevator> elevator;

  ElevatorTest()
  : number(0)
  , capacity(8)
  , floor(new Floor(0, 10))
  , elevator(new Elevator(number, capacity, floor))
  {}

  virtual ~ElevatorTest()
  {}
};

TEST_F(ElevatorTest, NoPassengers_ReturnsOccupation_Zero)
{
  EXPECT_EQ(elevator->getOccupation(), 0.f);
}

TEST_F(ElevatorTest, GetNumber)
{
  EXPECT_EQ(elevator->getNumber(), number);
}

TEST_F(ElevatorTest, GetCapacity)
{
  EXPECT_EQ(elevator->getCapacity(), capacity);
}

TEST_F(ElevatorTest, GetCurrentFloor)
{
  EXPECT_EQ(elevator->getCurrentFloor(), floor);
}
