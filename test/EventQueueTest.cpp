#include <gtest/gtest.h>
#include <memory>

#include "ClientArrival.h"
#include <glog/logging.h>
#include "EventQueue.h"

struct EventQueueTest : testing::Test
{
  int destination;
  int location;
  const std::shared_ptr<const Client> client;
  const std::shared_ptr<EventQueue> eventQueue;

  EventQueueTest()
  : destination(0)
  , location(0)
  , client(new Client(1, location, destination, 0, 0))
  , eventQueue(new EventQueue())
  {}

  virtual ~EventQueueTest()
  {}
};

TEST_F(EventQueueTest, HasNextEvent_BeforeInsertEvent_ReturnsFalse)
{
  EXPECT_FALSE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, HasNextEvent_AfterInsertEvent_ReturnsTrue)
{
  eventQueue->push(std::shared_ptr<const Event>(new ClientArrival(0, client)));
  EXPECT_TRUE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, Push_AddThreeEvents_ReturnsInPriorityOrder)
{
  auto e1 = std::shared_ptr<const Event>(new ClientArrival(10, client));
  auto e2 = std::shared_ptr<const Event>(new ClientArrival(50, client));
  auto e3 = std::shared_ptr<const Event>(new ClientArrival(30, client));

  eventQueue->push(e1);
  eventQueue->push(e2);
  eventQueue->push(e3);

  EXPECT_EQ(eventQueue->pop(), e1);
  EXPECT_EQ(eventQueue->pop(), e3);
  EXPECT_EQ(eventQueue->pop(), e2);
  EXPECT_FALSE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, Pop_EmptyQueue_ReturnsNullPointer)
{
  EXPECT_EQ(eventQueue->pop(), nullptr);
}
