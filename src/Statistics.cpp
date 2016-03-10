#include "Statistics.h"

Statistics::Statistics(Config& config)
 : config(config)
{}

void Statistics::reset(Config& config)
{
  this->config = config;
}

bool Statistics::keepRunning()
{
  return true;
}

void Statistics::notify(const Event& event)
{
  // Handle events
}