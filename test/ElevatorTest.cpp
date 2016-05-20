#include "Elevator.h"
#include "Client.h"
#include "Direction.h"
#include "Floor.h"
#include "Status.h"
#include <gtest/gtest.h>

struct ElevatorTest : testing::Test
{
  int number;
  int capacity;
  int location;
  std::pair<int, Direction> destination;

  std::shared_ptr<Elevator> elevator;

  ElevatorTest()
  : number(0)
  , capacity(8)
  , location(0)
  , destination(5, Direction::Up)
  , elevator(new Elevator(number, capacity, location))
  {}

  virtual ~ElevatorTest()
  {}
};

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
  EXPECT_EQ(elevator->getLocation(), location);
}

TEST_F(ElevatorTest, GetDestination)
{
  elevator->setDestination(destination);
  EXPECT_EQ(elevator->getDestination(), destination);
}
