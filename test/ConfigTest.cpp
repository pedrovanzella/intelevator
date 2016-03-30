#include <gtest/gtest.h>

#include "Config.h"
#include "easylogging++.h"
#include <memory>

struct ConfigTest : testing::Test
{
  const std::shared_ptr<Config> config;

  ConfigTest()
    : config(new Config("test_config.yaml"))
  {}

  virtual ~ConfigTest()
  {}
};

TEST_F(ConfigTest, SetInt_GetInt)
{
  config->setInt(Property::Elevators, 10);
  config->setInt(Property::Floors, 3);
  EXPECT_EQ(config->getInt(Property::Elevators), 10);
  EXPECT_EQ(config->getInt(Property::Floors), 3);
}

TEST_F(ConfigTest, SetString_GetString)
{
  config->setString(Property::Title, "teste");
  config->setString(Property::Dispatcher, "dispatcher");
  EXPECT_EQ(config->getString(Property::Title), "teste");
  EXPECT_EQ(config->getString(Property::Dispatcher), "dispatcher");
}