#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <queue>
#include "client.h"

class Floor {
public:
  int number;
  std::queue<std::shared_ptr<Client>> upLine;
  std::queue<std::shared_ptr<Client>> downLine;
};

#endif /* _FLOOR_H_ */
