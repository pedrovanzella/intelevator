#include <gtest/gtest.h>

#include "EventQueue.h"

struct EventQueueTest : testing::Test
{
  EventQueue* eventQueue;

  EventQueueTest()
  {
    eventQueue = new EventQueue();
  }

  virtual ~EventQueueTest()
  {
    delete eventQueue;
  }
};

TEST_F(EventQueueTest, HasNextEvent_BeforeInsertEvent_ReturnsFalse)
{
  EXPECT_FALSE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, HasNextEvent_AfterInsertEvent_ReturnsTrue)
{
  eventQueue->push(new Event(EventType::clientArrival, 0));
  EXPECT_TRUE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, Push_AddThreeEvents_ReturnsInPriorityOrder)
{
  Event* e1 = new Event(EventType::clientArrival, 100);
  Event* e2 = new Event(EventType::clientArrival, 50);
  Event* e3 = new Event(EventType::clientArrival, 75);

  eventQueue->push(e1);
  eventQueue->push(e2);
  eventQueue->push(e3);

  EXPECT_EQ(eventQueue->pop(), e2);
  EXPECT_EQ(eventQueue->pop(), e3);
  EXPECT_EQ(eventQueue->pop(), e1);
  EXPECT_FALSE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, Pop_EmptyQueue_ReturnsNullPointer)
{
  EXPECT_EQ(eventQueue->pop(), nullptr);
}