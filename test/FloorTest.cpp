#include <gtest/gtest.h>

#include "Floor.h"

struct FloorTest : testing::Test
{
  Floor* floor;
  int number = 0;

  FloorTest()
  {
    floor = new Floor(number);
  }

  virtual ~FloorTest()
  {
    delete floor;
  }
};