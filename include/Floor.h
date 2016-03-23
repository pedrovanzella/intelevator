#pragma once

#include <memory>
#include <queue>
#include "Client.h"
#include "EventObserver.h"
#include "Direction.h"

class Floor : public EventObserver
{
public:
  Floor(int number);
  virtual ~Floor();

  int getNumber() const;
  void notify(const std::shared_ptr<const Event> event) const;

    Direction compareTo(Floor& other);

private:
  int _number;
  std::queue<std::shared_ptr<const Client>> _upLine;
  std::queue<std::shared_ptr<const Client>> _downLine;
};
