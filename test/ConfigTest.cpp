#include <gtest/gtest.h>

#include "Config.h"
#include "easylogging++.h"
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

TEST_F(ConfigTest, SetInt_GetInt)
{
  config->setInt(Property::Elevators, 10);
  config->setInt(Property::Floors, 3);
  EXPECT_EQ(config->getInt(Property::Elevators), 10);
  EXPECT_EQ(config->getInt(Property::Floors), 3);
}

TEST_F(ConfigTest, SetFloat_GetFloat)
{
  config->setFloat(Property::Duration, 10.f);
  EXPECT_EQ(config->getFloat(Property::Duration),10.f);
}

TEST_F(ConfigTest, SetString_GetString)
{
  config->setString(Property::Title, "teste");
  config->setString(Property::Dispatcher, "dispatcher");
  EXPECT_EQ(config->getString(Property::Title), "teste");
  EXPECT_EQ(config->getString(Property::Dispatcher), "dispatcher");
}

// Config::from_file
TEST_F(ConfigTest, FromFile_Initializes)
{
  std::string str =
    "floors=4\n"
    "elevators=2\n"
    "maxLoad=150\n"
    "duration=20.0\n"
    "title=simple\n"
    "seed=666";

  std::istringstream sstream(str);

  config->fromFile(sstream);
  EXPECT_EQ(config->getInt(Property::Floors), 4);
  EXPECT_EQ(config->getInt(Property::Elevators), 2);
  EXPECT_EQ(config->getInt(Property::MaxLoad), 150);
  EXPECT_EQ(config->getInt(Property::Seed), 666);
  EXPECT_EQ(config->getFloat(Property::Duration), 20.0);
  EXPECT_EQ(config->getString(Property::Title), "simple");
}
