#include <gtest/gtest.h>

#include "Client.h"
#include "Floor.h"

struct ClientTest : testing::Test
{
  Client* client;
  const std::shared_ptr<const Floor> destination;

  int partySize;
  float arrivalTime;

  ClientTest()
  : destination(new Floor(0))
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
  EXPECT_EQ(client->getPartySize(), partySize);
}

TEST_F(ClientTest, GetArrivalTime_ReturnsArrivalTime)
{
  EXPECT_EQ(client->getArrivalTime(), arrivalTime);
}

TEST_F(ClientTest, GetDestination_ReturnsDestination)
{
  EXPECT_EQ(client->getDestination(), destination);
}
