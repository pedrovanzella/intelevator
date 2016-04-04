#pragma once

#include <memory>
#include <queue>
#include "Client.h"
#include "EventObserver.h"
#include "Direction.h"

class Floor : public EventObserver
{
public:
  Floor(int number, int population);
  virtual ~Floor();

  int getNumber() const;
  int getPopulation() const;
  void notify(const std::shared_ptr<const Event> event) const;

  Direction compareTo(const Floor& other) const;

private:
  int _number;
  int _population;
  std::queue<std::shared_ptr<const Client>> _upLine;
  std::queue<std::shared_ptr<const Client>> _downLine;
};
