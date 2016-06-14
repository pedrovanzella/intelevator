#include "StopManager.h"
#include "Direction.h"
#include "Elevator.h"
#include "Floor.h"
#include <gtest/gtest.h>

struct StopManagerTest : testing::Test {
  StopManager *sm;
  StopManagerTest() : sm(new StopManager()) {}

  virtual ~StopManagerTest() {}
};

TEST_F(StopManagerTest, GetNull) {
  auto f = std::make_shared<Floor>(0, 0);
  auto e = std::make_shared<Elevator>(0, 0, 0);
  EXPECT_EQ(false, sm->hasStop(f, Direction::Up));
  EXPECT_EQ(false, sm->hasStop(f, Direction::Down));

  EXPECT_EQ(0, sm->getStops(e, Direction::Up).size());
  EXPECT_EQ(0, sm->getStops(e, Direction::Down).size());
}

TEST_F(StopManagerTest, SetUp) {
  auto f = std::make_shared<Floor>(0, 0);
  auto d = Direction::Up;
  auto e = std::make_shared<Elevator>(0, 0, 0);
  sm->set(f, d, e);
  EXPECT_EQ(true, sm->hasStop(f, d));
  EXPECT_EQ(false, sm->hasStop(f, Direction::Down));
  auto stops = sm->getStops(e, d);
  EXPECT_EQ(1, stops.size());
  EXPECT_EQ(f, *stops.begin());

  sm->clear(f, e, d);
  EXPECT_EQ(false, sm->hasStop(f, d));

  stops = sm->getStops(e, d);
  EXPECT_EQ(0, stops.size());
  EXPECT_EQ(stops.end(), stops.begin());
}

TEST_F(StopManagerTest, SetDown) {
  auto f = std::make_shared<Floor>(0, 0);
  auto d = Direction::Down;
  auto e = std::make_shared<Elevator>(0, 0, 0);
  sm->set(f, d, e);
  EXPECT_EQ(true, sm->hasStop(f, d));
  EXPECT_EQ(false, sm->hasStop(f, Direction::Up));
  auto stops = sm->getStops(e, d);
  EXPECT_EQ(1, stops.size());
  EXPECT_EQ(f, *stops.begin());

  sm->clear(f, e, d);
  EXPECT_EQ(false, sm->hasStop(f, d));

  stops = sm->getStops(e, d);
  EXPECT_EQ(0, stops.size());
  EXPECT_EQ(stops.end(), stops.begin());
}

TEST_F(StopManagerTest, SetOverride) {
  auto f = std::make_shared<Floor>(0, 0);
  auto d = Direction::Down;
  auto e1 = std::make_shared<Elevator>(0, 0, 0);
  auto e2 = std::make_shared<Elevator>(0, 0, 0);

  sm->set(f, d, e1);
  EXPECT_EQ(true, sm->hasStop(f, d));

  auto stops1 = sm->getStops(e1, d);
  EXPECT_EQ(1, stops1.size());
  EXPECT_EQ(f, *stops1.begin());

  auto stops2 = sm->getStops(e2, d);
  EXPECT_EQ(0, stops2.size());
  EXPECT_EQ(stops2.end(), stops2.begin());

  sm->set(f, d, e2);
  EXPECT_EQ(true, sm->hasStop(f, d));

  stops1 = sm->getStops(e1, d);
  EXPECT_EQ(1, stops1.size());
  EXPECT_EQ(f, *stops1.begin());

  stops2 = sm->getStops(e2, d);
  EXPECT_EQ(1, stops2.size());
  EXPECT_EQ(f, *stops2.begin());
}

TEST_F(StopManagerTest, SetAndClear) {
  auto f1 = std::make_shared<Floor>(0, 0);
  auto f2 = std::make_shared<Floor>(1, 0);
  auto f3 = std::make_shared<Floor>(2, 0);
  auto e = std::make_shared<Elevator>(0, 0, 0);
  auto d = Direction::Down;

  sm->set(f1, d, e);
  sm->set(f2, d, e);
  sm->set(f3, d, e);

  EXPECT_EQ(true, sm->hasStop(f1, d));
  EXPECT_EQ(true, sm->hasStop(f2, d));
  EXPECT_EQ(true, sm->hasStop(f3, d));

  auto stops = sm->getStops(e, d);
  EXPECT_EQ(3, stops.size());
  EXPECT_NE(stops.end(), stops.find(f1));
  EXPECT_NE(stops.end(), stops.find(f2));
  EXPECT_NE(stops.end(), stops.find(f3));

  sm->clear(f2, e, d);

  stops = sm->getStops(e, d);
  EXPECT_EQ(2, stops.size());
  EXPECT_NE(stops.end(), stops.find(f1));
  EXPECT_EQ(stops.end(), stops.find(f2));
  EXPECT_NE(stops.end(), stops.find(f3));
}