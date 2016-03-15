#include <gtest/gtest.h>

#include "Clock.h"

struct ClockTest : testing::Test
{
  Clock* clock;
  Config config;

  ClockTest()
  {
    clock = new Clock(config);
  }

  virtual ~ClockTest()
  {
    delete clock;
  }
};

// Clock::advanceTo tests

TEST_F(ClockTest, AdvanceTo_FutureTime_Updates)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceTo(10.f);
  EXPECT_EQ(clock->currentTime(), 10.f);
}

TEST_F(ClockTest, AdvanceTo_PastTime_DoesntUpdate)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceTo(10.f);
  EXPECT_EQ(clock->currentTime(), 10.f);
  clock->advanceTo(5.f);
  EXPECT_EQ(clock->currentTime(), 10.f);
}

TEST_F(ClockTest, AdvanceTo_NegativeTime_DoesntUpdate)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceTo(-10.f);
  EXPECT_EQ(clock->currentTime(), 0.f);
}

TEST_F(ClockTest, AdvanceTo_CallTwice_UpdatesTwice)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceTo(10.f);
  EXPECT_EQ(clock->currentTime(), 10.f);
  clock->advanceTo(20.f);
  EXPECT_EQ(clock->currentTime(), 20.f);
}

// Clock::advanceBy tests

TEST_F(ClockTest, AdvanceBy_PositiveAmount_Advances)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceBy(10.f);
  EXPECT_EQ(clock->currentTime(), 10.f);
}

TEST_F(ClockTest, AdvanceBy_ZeroAmount_DoesntAdvance)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceBy(0.f);
  EXPECT_EQ(clock->currentTime(), 0.f);
}

TEST_F(ClockTest, AdvanceBy_NegativeAmount_DoesntAdvance)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceBy(-10.f);
  EXPECT_EQ(clock->currentTime(), 0.f);
}

TEST_F(ClockTest, AdvanceBy_CallTwice_AdvancesTwice)
{
  EXPECT_EQ(clock->currentTime(), 0.f);
  clock->advanceBy(10.f);
  EXPECT_EQ(clock->currentTime(), 10.f);
  clock->advanceBy(20.f);
  EXPECT_EQ(clock->currentTime(), 30.f);
}
