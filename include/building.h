#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <set>
#include <list>
#include "elevator.h"
#include "floor.h"
#include "config.h"

class Building {
private:
  std::set<Elevator> elevators;
  std::list<Floor> floors;

public:
  void reset(std::shared_ptr<Config> config);
};

#endif /* _BUILDING_H_ */
