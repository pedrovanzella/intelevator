#include <gtest/gtest.h>
#include <memory>

#include "Client.h"
#include "Floor.h"

struct ClientTest : testing::Test
{
  int partySize;
  float arrivalTime;
  int destination;
  int location;
  const std::shared_ptr<const Client> client;

  ClientTest()
  : partySize(1)
  , arrivalTime(10.f)
  , destination(0)
    ,location(0)
  , client(new Client(partySize, arrivalTime, location, destination))
  {}

  virtual ~ClientTest()
  {}
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
