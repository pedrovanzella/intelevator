#include <gtest/gtest.h>
#include <memory>

#include "ClientArrival.h"
#include "easylogging++.h"
#include "EventQueue.h"

struct EventQueueTest : testing::Test
{
  const std::shared_ptr<const Floor> destination;
  const std::shared_ptr<const Client> client;
  const std::shared_ptr<EventQueue> eventQueue;

  EventQueueTest()
  : destination(new Floor(0, 10))
  , client(new Client(1, 0.f, destination))
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
  eventQueue->push(std::shared_ptr<const Event>(new ClientArrival(0, client, destination)));
  EXPECT_TRUE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, Push_AddThreeEvents_ReturnsInPriorityOrder)
{
  auto e1 = std::shared_ptr<const Event>(new ClientArrival(10, client, destination));
  auto e2 = std::shared_ptr<const Event>(new ClientArrival(50, client, destination));
  auto e3 = std::shared_ptr<const Event>(new ClientArrival(30, client, destination));

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
