#include <gtest/gtest.h>

#include "ClientArrival.h"
#include "EventQueue.h"

struct EventQueueTest : testing::Test
{
  EventQueue* eventQueue;

  const std::shared_ptr<const Floor> destination;
  Client* client;

  EventQueueTest()
  : destination(new Floor(0))
  {
    eventQueue = new EventQueue();
    client = new Client(1, 0.f, destination);
  }

  virtual ~EventQueueTest()
  {
    delete client;
    delete eventQueue;
  }
};

TEST_F(EventQueueTest, HasNextEvent_BeforeInsertEvent_ReturnsFalse)
{
  EXPECT_FALSE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, HasNextEvent_AfterInsertEvent_ReturnsTrue)
{
  eventQueue->push(new ClientArrival(0.f, *client));
  EXPECT_TRUE(eventQueue->hasNextEvent());
}

TEST_F(EventQueueTest, Push_AddThreeEvents_ReturnsInPriorityOrder)
{
  Event* e1 = new ClientArrival(10.f, *client);
  Event* e2 = new ClientArrival(50.f, *client);
  Event* e3 = new ClientArrival(30.f, *client);

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