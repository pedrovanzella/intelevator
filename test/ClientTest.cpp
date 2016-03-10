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

TEST_F(ClientTest, GetPartySize_ReturnsPartySize)
{
  EXPECT_EQ(client->partySize, partySize);
}

TEST_F(ClientTest, GetArrivalTime_ReturnsArrivalTime)
{
  EXPECT_EQ(client->arrivalTime, arrivalTime);
}

TEST_F(ClientTest, GetDestination_ReturnsDestination)
{
  EXPECT_EQ(&client->destination, &destination);
}
