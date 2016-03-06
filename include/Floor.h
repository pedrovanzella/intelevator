#pragma once

#include <queue>
#include "Client.h"

class Floor {
public:
  int number;
  std::queue<Client*> upLine;
  std::queue<Client*> downLine;

  Floor();
};