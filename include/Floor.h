#pragma once

#include <queue>
#include "Client.h"
#include "EventObserver.h"

class Floor : public EventObserver
{
public:
  Floor(int number);
  virtual ~Floor();

  int getNumber() const;
  void notify(const Event&) const;

private:
  int _number;
  std::queue<Client*> _upLine;
  std::queue<Client*> _downLine;
};
