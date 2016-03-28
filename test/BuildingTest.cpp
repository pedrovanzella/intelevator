#include <gtest/gtest.h>
#include <iostream>
#include <memory>

#include "Building.h"
#include "easylogging++.h"
#include "Elevator.h"
#include "Floor.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

struct BuildingTest : testing::Test
{
  std::shared_ptr<Config> config;
  std::shared_ptr<Building> building;

  BuildingTest()
    : config(new Config())
    , building(new Building(config))
  {
    config->setString(Property::Dispatcher, "Dummy");
    config->setInt(Property::Floors, 3);
    config->setInt(Property::Elevators, 5);

    building->initialize();
  }

  virtual ~BuildingTest()
  {}
};

TEST_F(BuildingTest, GetConfig_ReturnsConfig)
{
  EXPECT_EQ(config, building->getConfig());
}

TEST_F(BuildingTest, GetFloors_ReturnsRightSize)
{
  EXPECT_EQ(config->getInt(Property::Floors), building->getFloors().size());
}

TEST_F(BuildingTest, GetElevators_ReturnsRightSize)
{
  EXPECT_EQ(config->getInt(Property::Elevators), building->getElevators().size());
}

TEST_F(BuildingTest, GetLocation_NewBuilding_ReturnsLobby)
{
  auto lobby = building->getFloors().front();
  for (auto e : building->getElevators())
  {
    EXPECT_EQ(lobby, building->getLocation(e));
  }
}

TEST_F(BuildingTest, SetLocation_UpdatesLocation)
{
  auto roof = building->getFloors().back();
  auto e = building->getElevators().front();
  building->setLocation(e, roof);
  EXPECT_EQ(roof, building->getLocation(e));
}


TEST_F(BuildingTest, GetLobby_ReturnsLobby) {
  EXPECT_EQ(building->getLobby()->getNumber(), 1);
}
