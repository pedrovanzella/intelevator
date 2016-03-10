#pragma once

#include "Event.h"

struct EventComparator {
  bool operator()(Event* e1, Event* e2)
  {
    return e1->getTime() > e2->getTime();
  }
};