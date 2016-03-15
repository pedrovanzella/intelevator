#include "Statistics.h"

Statistics::Statistics(Config& config)
 : _config(config)
{}

bool Statistics::keepRunning() const
{
  return true;
}

void Statistics::notify(const Event& event) const
{
  // Handle events
}
