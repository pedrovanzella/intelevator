#include <gtest/gtest.h>

#include "Clock.h"
#include "easylogging++.h"

struct ClockTest : testing::Test
{
  Clock* clock;
  std::shared_ptr<Config> config;

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
  EXPECT_EQ(clock->currentTime(), 0ul);
  clock->advanceTo(10ul);
  EXPECT_EQ(clock->currentTime(), 10ul);
}

TEST_F(ClockTest, AdvanceTo_PastTime_DoesntUpdate)
{
  EXPECT_EQ(clock->currentTime(), 0ul);
  clock->advanceTo(10ul);
  EXPECT_EQ(clock->currentTime(), 10ul);
  clock->advanceTo(5ul);
  EXPECT_EQ(clock->currentTime(), 10ul);
}

TEST_F(ClockTest, AdvanceTo_CallTwice_UpdatesTwice)
{
  EXPECT_EQ(clock->currentTime(), 0ul);
  clock->advanceTo(10ul);
  EXPECT_EQ(clock->currentTime(), 10ul);
  clock->advanceTo(20ul);
  EXPECT_EQ(clock->currentTime(), 20ul);
}

// Clock::advanceBy tests

TEST_F(ClockTest, AdvanceBy_PositiveAmount_Advances)
{
  EXPECT_EQ(clock->currentTime(), 0ul);
  clock->advanceBy(10ul);
  EXPECT_EQ(clock->currentTime(), 10ul);
}

TEST_F(ClockTest, AdvanceBy_ZeroAmount_DoesntAdvance)
{
  EXPECT_EQ(clock->currentTime(), 0ul);
  clock->advanceBy(0ul);
  EXPECT_EQ(clock->currentTime(), 0ul);
}

TEST_F(ClockTest, AdvanceBy_CallTwice_AdvancesTwice)
{
  EXPECT_EQ(clock->currentTime(), 0ul);
  clock->advanceBy(10ul);
  EXPECT_EQ(clock->currentTime(), 10ul);
  clock->advanceBy(20ul);
  EXPECT_EQ(clock->currentTime(), 30ul);
}
