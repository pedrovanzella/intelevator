#include <gtest/gtest.h>
#include <memory>
#include "ClientArrival.h"

struct ClientArrivalTest : testing::Test
{
  int partySize;
  float arrivalTime;
  int destination;
  int location;
  const std::shared_ptr<const Client> client;
  const std::shared_ptr<const ClientArrival> clientArrival;

  ClientArrivalTest()
  : partySize(1)
  , arrivalTime(10)
  , destination(0)
  , location(0)
  , client(new Client(partySize, location, destination))
  , clientArrival(new ClientArrival(arrivalTime, client))
  {}

  virtual ~ClientArrivalTest()
  {}
};

TEST_F(ClientArrivalTest, GetClient_ReturnsClient)
{
  EXPECT_EQ(clientArrival->getClient(), client);
}
