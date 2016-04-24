#include "EventFactory.h"
#include "Simulator.h"

EventFactory::EventFactory(std::shared_ptr<Simulator> simulator)
    : _simulator(simulator) {}

EventFactory::~EventFactory() {}

std::shared_ptr<std::vector<std::shared_ptr<EventFactory>>> EventFactory::create(std::shared_ptr<Simulator> simulator) {
  std::shared_ptr<std::vector<std::shared_ptr<EventFactory>>> factories(new std::vector<std::shared_ptr<EventFactory>>);

  // for (auto it : simulator->getScenario()->getFloors()) {
  //   auto ef = std::make_shared<EventFactory>(simulator);
  //   factories->push_back(ef);
  // }

  return factories;
}