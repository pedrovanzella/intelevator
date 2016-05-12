#include <gtest/gtest.h>
#include <memory>

#include "Floor.h"
#include "Direction.h"

struct FloorTest : testing::Test
{
  int number = 1;
  float lambda = 5;
  int population = 10;
  std::shared_ptr<Floor> floor;

  FloorTest()
    : number(1), lambda(5), population(10),
      floor(new Floor(number, population, lambda)) {}

  virtual ~FloorTest() {}
};

TEST_F(FloorTest, GetNumber)
{
  EXPECT_EQ(floor->getNumber(), number);
}

TEST_F(FloorTest, GetLambda)
{
  EXPECT_EQ(floor->getLambda(), lambda);
}

TEST_F(FloorTest, GetPopulation)
{
  EXPECT_EQ(floor->getPopulation(), population);
}

TEST_F(FloorTest, CompareTo)
{
  Floor down(0, 0, 0);
  EXPECT_EQ(floor->compareTo(down), Direction::Down);

  Floor up(2, 0, 0);
  EXPECT_EQ(floor->compareTo(up), Direction::Up);

  Floor none(1, 0, 0);
  EXPECT_EQ(floor->compareTo(none), Direction::None);
}

TEST_F(FloorTest, AddClient)
{
  int beforeSize = floor->clientsOnUpLine();
  auto clientGoingUp = std::make_shared<Client>(0, 0, 2, 0);
  floor->addClient(clientGoingUp);
  EXPECT_EQ(beforeSize + 1, floor->clientsOnUpLine());

  beforeSize = floor->clientsOnDownLine();
  auto clientGoingDown = std::make_shared<Client>(0, 0, 0, 0);
  floor->addClient(clientGoingDown);
  EXPECT_EQ(beforeSize + 1, floor->clientsOnDownLine());
}
