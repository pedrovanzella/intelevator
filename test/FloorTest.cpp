#include <gtest/gtest.h>

#include "Floor.h"
#include "Direction.h"

struct FloorTest : testing::Test
{
  Floor* floor;
  int number = 1;

  FloorTest()
  {
    floor = new Floor(number);
  }

  virtual ~FloorTest()
  {
    delete floor;
  }
};

TEST_F(FloorTest, FloorTest_CompareTo_Test)
{
  Floor down(0);
  EXPECT_EQ(floor->compareTo(down), Direction::descending);

  Floor up(2);
  EXPECT_EQ(floor->compareTo(up), Direction::ascending);

  EXPECT_EQ(floor->compareTo(*floor), Direction::idle);
}