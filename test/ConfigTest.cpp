#include <gtest/gtest.h>

#include "Config.h"

struct ConfigTest : testing::Test
{
  Config* config;

  ConfigTest()
  {
    config = new Config();
  }

  virtual ~ConfigTest()
  {
    delete config;
  }
};

// Config::from_file
TEST_F(ConfigTest, FromFile_Initializes)
{
  config->from_file("test/mocks/config/simple.conf");
  EXPECT_EQ(config->floors, 4);
  EXPECT_EQ(config->elevators, 2);
  EXPECT_EQ(config->maxLoad, 150);
  EXPECT_EQ(config->duration, 20.0);
  EXPECT_EQ(config->title, "simple");
  EXPECT_EQ(config->seed, 666);
}
