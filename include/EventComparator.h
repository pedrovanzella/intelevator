#pragma once

#include "Event.h"

class EventComparator
{
public:
  bool operator()(const Event* e1, const Event* e2) const;
};
