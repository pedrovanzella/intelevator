#pragma once

#include <queue>
#include "client.h"

class Floor {
public:
  int number;
  std::queue<std::shared_ptr<Client>> upLine;
  std::queue<std::shared_ptr<Client>> downLine;
};