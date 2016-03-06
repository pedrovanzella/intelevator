#pragma once

class Floor; // forward declaration

class Client {
public:
  int partySize;
  double arrivalTime;
  Floor* destination;

  Client();
};