#include "EventFactory.h"

EventFactory::EventFactory(const std::string seed)
    : _seed_sequence(seed.begin(), seed.end()) {}

EventFactory::~EventFactory() {}
