#pragma once

class Floor; // forward declaration

class Client {
public:
  Client(const int partySize, const float arrivalTime, const Floor& destination);

  const int _partySize;
  const float _arrivalTime;
  const Floor& _destination;
};