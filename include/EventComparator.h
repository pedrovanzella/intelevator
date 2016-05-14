#pragma once

#include <memory>

class Event;

class EventComparator {
public:
  bool operator()(std::shared_ptr<const Event> e1,
                  std::shared_ptr<const Event> e2) const;
};
