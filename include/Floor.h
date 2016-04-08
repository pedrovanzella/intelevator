#pragma once

#include <memory>
#include <queue>
#include "Client.h"
#include "EventObserver.h"
#include "Direction.h"

class Floor
{
public:
  Floor(int number, int population);
  virtual ~Floor();

  int getNumber() const;
  int getPopulation() const;
  Direction compareTo(const Floor& other) const;
  bool hasUpCall() const;
  bool hasDownCall() const;

  void addClient(const std::shared_ptr<const Client> client);

private:
  int _number;
  int _population;
  std::queue<std::shared_ptr<const Client>> _upLine;
  std::queue<std::shared_ptr<const Client>> _downLine;
};
