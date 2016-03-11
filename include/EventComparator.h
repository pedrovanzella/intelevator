#pragma once

#include "Event.h"

class EventComparator
{
public:
  bool operator()(Event* e1, Event* e2);
};