#pragma once

#include <queue>
#include "Client.h"
#include "EventObserver.h"

class Floor : public EventObserver
{
public:
  Floor(int);
  int getNumber();
  void notify(const Event&);

private:
  int number;
  std::queue<Client*> upLine;
  std::queue<Client*> downLine;
};