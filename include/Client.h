#pragma once

class Floor; // forward declaration

class Client {
public:
  Client(const int, const float, const Floor&);

  const int partySize;
  const float arrivalTime;
  const Floor& destination;
};