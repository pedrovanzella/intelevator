#include <glog/logging.h>
#include "Statistics.h"

Statistics::Statistics()
{
}

Statistics::~Statistics()
{
}

bool Statistics::keepRunning() const
{
  return true;
}

void Statistics::notify(const std::shared_ptr<const Event> event)
{
  // Handle events
}
