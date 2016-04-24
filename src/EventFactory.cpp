#include "Clock.h"
#include "EventFactory.h"
#include "Floor.h"

EventFactory::EventFactory(std::shared_ptr<Clock> clock, std::shared_ptr<Floor> floor)
    : _clock(clock), _floor(floor) {}

EventFactory::~EventFactory() {}
