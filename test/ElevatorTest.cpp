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
  EXPECT_EQ(location, elevator->getLocation());
  EXPECT_EQ(Status::Idle, elevator->getStatus());

  elevator->setDestination(destination);
  EXPECT_EQ(destination, elevator->getDestination());
  EXPECT_EQ(Status::Moving, elevator->getStatus());
  EXPECT_EQ(Direction::Up, elevator->getDirection());

  for (int i = location; i < destination - 1; i++)
  {
    elevator->update();
    EXPECT_EQ(i + 1, elevator->getLocation());
    EXPECT_EQ(Status::Moving, elevator->getStatus());
  }

  elevator->update();
  EXPECT_EQ(location + destination, elevator->getLocation());

  elevator->stop();
  EXPECT_EQ(Status::Stopped, elevator->getStatus());
}

TEST_F(ElevatorTest, MoveDown)
{
  location = 5;
  elevator->setLocation(location);
  EXPECT_EQ(location, elevator->getLocation());
  EXPECT_EQ(Status::Idle, elevator->getStatus());

  destination = 0;
  elevator->setDestination(destination);
  EXPECT_EQ(destination, elevator->getDestination());
  EXPECT_EQ(Status::Moving, elevator->getStatus());
  EXPECT_EQ(Direction::Down, elevator->getDirection());

  for (int i = location; i > destination + 1; i--)
  {
    elevator->update();
    EXPECT_EQ(i - 1, elevator->getLocation());
    EXPECT_EQ(Status::Moving, elevator->getStatus());
  }

  elevator->update();
  EXPECT_EQ(destination, elevator->getLocation());

  elevator->stop();
  EXPECT_EQ(Status::Stopped, elevator->getStatus());
}

TEST_F(ElevatorTest, DropPassengersToCurrentLocation)
{
  for (int destination = 0; destination < 10; destination++)
  {
    for (int i = 0; i < 3; i++)
    {
      int passengersBefore = elevator->getPassengers()->size();
      std::shared_ptr<Client> c(new Client(1, 0, destination, 0));
      elevator->addPassenger(c);
      EXPECT_EQ(passengersBefore + 1, elevator->getPassengers()->size());
    }
  }

  for (int destination = 0; destination < 10; destination++)
  {
    int passengersBefore = elevator->getPassengers()->size();
    elevator->setLocation(destination);
    auto ps = elevator->dropPassengersToCurrentLocation();
    EXPECT_EQ(3, ps->size());
    EXPECT_EQ(passengersBefore - 3, elevator->getPassengers()->size());
  }
}