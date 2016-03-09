#include <gtest/gtest.h>

#include "Client.h"
#include "Floor.h"

struct ClientTest : testing::Test
{
  Client* client;
  Floor destination;

  int partySize;
  float arrivalTime;

  ClientTest()
  {
    partySize = 1;
    arrivalTime = 10.f;
    client = new Client(partySize, arrivalTime, destination);
  }

  virtual ~ClientTest()
  {
    delete client;
  }
};

TEST_F(ClientTest, CanGetPartySize)
{
  EXPECT_EQ(client->getPartySize(), partySize);
}

TEST_F(ClientTest, CanGetArrivalTime)
{
  EXPECT_EQ(client->getArrivalTime(), arrivalTime);
}

TEST_F(ClientTest, CanGetDestination)
{
  EXPECT_EQ(&client->getDestination(), &destination);
}