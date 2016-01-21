#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <queue>
#include "client.h"

class Floor {
public:
  int number;
  std::queue<Client> upLine;
  std::queue<Client> downLine;
};

#endif /* _FLOOR_H_ */
