#include <gtest/gtest.h>

#include "Config.h"
#include <sstream>

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
  std::string str =
    "floors=4"
    "elevators=2"
    "maxLoad=150"
    "duration=20.0"
    "title=simple"
    "seed=666";

  std::istringstream sstream(str);

  config->from_file(sstream);
  EXPECT_EQ(config->floors, 4);
  EXPECT_EQ(config->elevators, 2);
  EXPECT_EQ(config->maxLoad, 150);
  EXPECT_EQ(config->duration, 20.0);
  EXPECT_EQ(config->title, "simple");
  EXPECT_EQ(config->seed, 666);
}
