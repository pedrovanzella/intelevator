#include "Event.h"
#include "EventComparator.h"

bool EventComparator::operator()(std::shared_ptr<const Event> e1,
                                 std::shared_ptr<const Event> e2) const {
  return e1->getTime() > e2->getTime();
}
