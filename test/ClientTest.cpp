#include <gtest/gtest.h>
#include <memory>

#include "Client.h"
#include "Floor.h"

struct ClientTest : testing::Test
{
  int partySize;
  int destination;
  int arrivalFloor;
  const std::shared_ptr<const Client> client;

  ClientTest()
  : partySize(1)
  , destination(10)
  , arrivalFloor(0)
  , client(new Client(partySize, arrivalFloor, destination, 0, 0))
  {}

  virtual ~ClientTest()
  {}
};

TEST_F(ClientTest, GetPartySize_ReturnsPartySize)
{
  EXPECT_EQ(client->getPartySize(), partySize);
}

TEST_F(ClientTest, GetArrivalFloor_ReturnsArrivalFloor)
{
  EXPECT_EQ(client->getArrivalFloor(), arrivalFloor);
}


TEST_F(ClientTest, GetDestination_ReturnsDestination)
{
  EXPECT_EQ(client->getDestination(), destination);
}
