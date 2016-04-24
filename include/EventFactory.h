#pragma once

#include <glog/logging.h>
#include <memory>

class Clock;
class Floor;

class EventFactory
{
public:
  EventFactory(std::shared_ptr<Clock> clock, std::shared_ptr<Floor> floor);
  virtual ~EventFactory();

private:
  std::shared_ptr<Clock> _clock;
  std::shared_ptr<Floor> _floor;
};
