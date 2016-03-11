#include "EventComparator.h"

bool EventComparator::operator()(const Event* e1, const Event* e2) const
{
  return e1->getTime() > e2->getTime();
}
