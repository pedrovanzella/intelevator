#ifndef _STATISTICS_H_
#define _STATISTICS_H_

#include <list>
#include "trip.h"
#include "config.h"

class Statistics {
public:
  std::list<std::shared_ptr<Trip>> trips;

  void reset(Config config);
  bool keepRunning();
};

#endif /* _STATISTICS_H_ */
