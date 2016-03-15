#include <gtest/gtest.h>
#include <iostream>

#include "Building.h"
#include "Elevator.h"
#include "Floor.h"

using namespace std;

struct BuildingTest : testing::Test
{
  Config* config;
  Building* building;

  BuildingTest()
  {
    config = new Config();
    config->_floors = 3;
    config->_elevators = 5;

    building = new Building(*config);
  }

  virtual ~BuildingTest()
  {
    delete building;
    delete config;
  }
};

TEST_F(BuildingTest, GetConfig_ReturnsConfig)
{
  EXPECT_EQ(config, &building->getConfig());
}

TEST_F(BuildingTest, GetFloors_ReturnsRightSize)
{
  EXPECT_EQ(config->_floors, building->getFloors().size());
}

TEST_F(BuildingTest, GetElevators_ReturnsRightSize)
{
  EXPECT_EQ(config->_elevators, building->getElevators().size());
}

TEST_F(BuildingTest, GetLocation_NewBuilding_ReturnsLobby)
{
  Floor* lobby = building->getFloors().front();
  for (auto e : building->getElevators())
  {
    EXPECT_EQ(lobby, building->getLocation(e));
  }
}

TEST_F(BuildingTest, SetLocation_ArbitraryElevator_UpdatesLocation)
{
  Floor* lobby = building->getFloors().front();
  Floor* roof = building->getFloors().back();
  Elevator* e = building->getElevators().front();
  building->setLocation(e, roof);
  EXPECT_EQ(roof, building->getLocation(e));
  building->setLocation(e, lobby);
  EXPECT_EQ(lobby, building->getLocation(e));
}
