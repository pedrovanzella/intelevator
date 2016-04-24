#include "Clock.h"
#include "EventFactory.h"
#include "Floor.h"

EventFactory::EventFactory(std::shared_ptr<Clock> clock,
                           std::shared_ptr<Floor> floor, std::string seed)
    : _clock(clock), _floor(floor), _seed(seed.begin(), seed.end()),
      _generator(_seed), _distribution(floor->getLambda()) {}

EventFactory::~EventFactory() {}
