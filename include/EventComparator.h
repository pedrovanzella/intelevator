#pragma once

#include "Event.h"

struct EventComparator {
  bool operator()(const Event* e1, const Event* e2)
  {
    return e1->eventTime > e2->eventTime;
  }
};