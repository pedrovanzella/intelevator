#include <gtest/gtest.h>

#include "Elevator.h"
#include "Floor.h"

struct ElevatorTest : testing::Test
{
  int number;
  int capacity;
  int location;
  int destination;

  std::shared_ptr<Elevator> elevator;

  ElevatorTest()
  : number(0)
  , capacity(8)
  , location(0)
  , destination(5)
  , elevator(new Elevator(number, capacity, location))
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
  EXPECT_EQ(elevator->getLocation(), location);
}

TEST_F(ElevatorTest, GetDestination)
{
  elevator->setDestination(destination);
  EXPECT_EQ(elevator->getDestination(), destination);
}

TEST_F(ElevatorTest, MoveUp)
{
  EXPECT_EQ(elevator->getLocation(), location);
  EXPECT_EQ(elevator->getStatus(), Status::Stopped);

  elevator->setDestination(destination);
  EXPECT_EQ(elevator->getDestination(), destination);

  elevator->start();

  EXPECT_EQ(elevator->getDirection(), Direction::Up);

  for (int i = location; i < destination - 1; i++)
  {
    elevator->move();
    EXPECT_EQ(elevator->getLocation(), i + 1);
    EXPECT_EQ(elevator->getStatus(), Status::Moving);
  }

  elevator->move();
  EXPECT_EQ(elevator->getLocation(), location + destination);

  elevator->stop();
  EXPECT_EQ(elevator->getStatus(), Status::Stopped);
}

TEST_F(ElevatorTest, MoveDown)
{
  location = 5;
  elevator->setLocation(location);
  EXPECT_EQ(elevator->getLocation(), location);

  destination = 0;
  elevator->setDestination(destination);
  EXPECT_EQ(elevator->getDestination(), destination);

  elevator->turn();
  elevator->start();

  EXPECT_EQ(elevator->getDirection(), Direction::Down);
  EXPECT_EQ(elevator->getStatus(), Status::Moving);

  for (int i = location; i > destination + 1; i--)
  {
    elevator->move();
    EXPECT_EQ(elevator->getLocation(), i - 1);
    EXPECT_EQ(elevator->getStatus(), Status::Moving);
  }

  elevator->move();
  EXPECT_EQ(elevator->getLocation(), destination);

  elevator->stop();
  EXPECT_EQ(elevator->getStatus(), Status::Stopped);
}
