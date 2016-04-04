#include <gtest/gtest.h>
#include <memory>

#include "Floor.h"
#include "Direction.h"

struct FloorTest : testing::Test
{
  int number = 1;
  int population = 10;
  std::shared_ptr<Floor> floor;

  FloorTest()
   : number(1)
   , population(10)
   , floor(new Floor(number, population))
   {}

  virtual ~FloorTest()
  {}
};

TEST_F(FloorTest, GetNumber)
{
  EXPECT_EQ(floor->getNumber(), number);
}

TEST_F(FloorTest, GetPopulation)
{
  EXPECT_EQ(floor->getPopulation(), population);
}

TEST_F(FloorTest, CompareTo)
{
  Floor down(0, 10);
  EXPECT_EQ(floor->compareTo(down), Direction::descending);

  Floor up(2, 10);
  EXPECT_EQ(floor->compareTo(up), Direction::ascending);

  EXPECT_EQ(floor->compareTo(*floor), Direction::idle);
}
