#include "Simulator.h"
#include <iostream>

Simulator::Simulator(Config& config)
  : _config()
  , _building(_config)
  , _statistics(_config)
  , _clock(_config)
  , _eventQueue()
  , _eventDispatcher()
{
  _eventDispatcher.subscribe(std::shared_ptr<const EventObserver>(static_cast<EventObserver*>(&_building)));
  _eventDispatcher.subscribe(std::shared_ptr<const EventObserver>(static_cast<EventObserver*>(&_statistics)));
  _eventDispatcher.subscribe(std::shared_ptr<const EventObserver>(static_cast<EventObserver*>(&_clock)));
}

Simulator::~Simulator()
{
  _eventDispatcher.unsubscribe(std::shared_ptr<const EventObserver>(static_cast<EventObserver*>(&_building)));
  _eventDispatcher.unsubscribe(std::shared_ptr<const EventObserver>(static_cast<EventObserver*>(&_statistics)));
  _eventDispatcher.unsubscribe(std::shared_ptr<const EventObserver>(static_cast<EventObserver*>(&_clock)));
}

void Simulator::Run()
{
  std::cout << "Simulator is running" << std::endl;
  while (_statistics.keepRunning() && _eventQueue.hasNextEvent())
  {
    Event* e = _eventQueue.pop();
    _eventDispatcher.broadcast(std::shared_ptr<const Event>(e));
    delete e;
  }
}

bool Simulator::NextStep()
{
  return true;
}

