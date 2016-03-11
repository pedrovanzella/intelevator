#include "Statistics.h"

Statistics::Statistics(Config& config)
 : config(config)
{}

void Statistics::reset(Config& config)
{
  this->config = config;
}

bool Statistics::keepRunning() const
{
  return true;
}

void Statistics::notify(const Event& event) const
{
  // Handle events
}
