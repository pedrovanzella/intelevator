#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include <queue>
#include <map>
#include <set>
#include "floor.h"
#include "client.h"
#include "direction.h"

class Elevator {
public:
  Floor currentFloor;
  std::queue<Floor> destinations;
  std::map<Floor, std::set<Client>> passengers;

  Direction direction();
  int occupation();
};

#endif /* _ELEVATOR_H_ */
