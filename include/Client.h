#pragma once

class Floor; // forward declaration

class Client {
private:
  const int partySize;
  const float arrivalTime;
  const Floor& destination;

public:
  Client(const int, const float, const Floor&);

  const int getPartySize();
  const float getArrivalTime();
  const Floor& getDestination();
};