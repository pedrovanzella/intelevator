#include "easylogging++.h"
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

void Statistics::notify(const std::shared_ptr<const Event> event) const
{
  // Handle events
}
