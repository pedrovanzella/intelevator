#include <gtest/gtest.h>

#include "Timer.h"

struct TimerTest : testing::Test
{
  Timer* timer;
  Config config;

  TimerTest()
  {
    timer = new Timer(config);
  }

  virtual ~TimerTest()
  {
    delete timer;
  }
};

// Timer::advanceTo tests

TEST_F(TimerTest, AdvanceTo_FutureTime_Updates)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceTo(10.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
}

TEST_F(TimerTest, AdvanceTo_PastTime_DoesntUpdate)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceTo(10.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
  timer->advanceTo(5.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
}

TEST_F(TimerTest, AdvanceTo_NegativeTime_DoesntUpdate)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceTo(-10.f);
  EXPECT_EQ(timer->currentTime(), 0.f);
}

TEST_F(TimerTest, AdvanceTo_CallTwice_UpdatesTwice)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceTo(10.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
  timer->advanceTo(20.f);
  EXPECT_EQ(timer->currentTime(), 20.f);
}

// Timer::advanceBy tests

TEST_F(TimerTest, AdvanceBy_PositiveAmount_Advances)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceBy(10.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
}

TEST_F(TimerTest, AdvanceBy_ZeroAmount_DoesntAdvance)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceBy(0.f);
  EXPECT_EQ(timer->currentTime(), 0.f);
}

TEST_F(TimerTest, AdvanceBy_NegativeAmount_DoesntAdvance)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceBy(-10.f);
  EXPECT_EQ(timer->currentTime(), 0.f);
}

TEST_F(TimerTest, AdvanceBy_CallTwice_AdvancesTwice)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceBy(10.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
  timer->advanceBy(20.f);
  EXPECT_EQ(timer->currentTime(), 30.f);
}

// Timer::reset tests

TEST_F(TimerTest, Reset_AdvancedTime_Resets)
{
  EXPECT_EQ(timer->currentTime(), 0.f);
  timer->advanceBy(10.f);
  EXPECT_EQ(timer->currentTime(), 10.f);
  timer->reset(config);
  EXPECT_EQ(timer->currentTime(), 0.f);
}