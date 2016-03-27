#include "easylogging++.h"
#include "Statistics.h"

Statistics::Statistics(const std::shared_ptr<const Config> config)
 : _config(config)
{
  LOG(TRACE) << "Statistics created.";
}

Statistics::~Statistics()
{
  LOG(TRACE) << "Statistics destroyed.";
}

bool Statistics::keepRunning() const
{
  return true;
}

void Statistics::notify(const std::shared_ptr<const Event> event) const
{
  // Handle events
}
