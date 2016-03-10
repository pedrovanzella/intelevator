#pragma once

#include <queue>
#include "Building.h"
#include "Client.h"
#include "EventObserver.h"

class Floor : public EventObserver
{
public:
  Floor(const Building&, int);
  virtual ~Floor();

  const Building& getBuilding();
  int getNumber();
  void notify(const Event&);

private:
  const Building& building;
  int number;
  std::queue<Client*> upLine;
  std::queue<Client*> downLine;
};