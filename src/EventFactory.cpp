#include "EventFactory.h"
#include "Simulator.h"

EventFactory::EventFactory(std::shared_ptr<Simulator> simulator)
    : _simulator(simulator) {}

EventFactory::~EventFactory() {}

std::shared_ptr<std::vector<std::shared_ptr<EventFactory>>> EventFactory::create(std::shared_ptr<Simulator> simulator) {
  std::shared_ptr<std::vector<std::shared_ptr<EventFactory>>> factories(new std::vector<std::shared_ptr<EventFactory>>);

  auto floorCount = simulator->getScenario()->getPopulation().size();

  for (int i = 0; i < floorCount; i++) {
    auto ef = std::make_shared<EventFactory>(simulator);
    factories->push_back(ef);
  }

  return factories;
}