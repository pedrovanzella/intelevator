#include "Simulator.h"
#include "Building.h"
#include "Client.h"
#include "ClientArrival.h"
#include "Clock.h"
#include "CostFunctionCreator.h"
#include "CostFunctionType.h"
#include "SchedulerCreator.h"
#include "SchedulerType.h"
#include "EventDispatcher.h"
#include "EventQueue.h"
#include "FinishSimulation.h"
#include "Floor.h"
#include "Scenario.h"
#include "Statistics.h"
#include "SchedulerType.h"
#include "CostFunctionType.h"
#include "Elevator.h"
#include <glog/logging.h>
#include <random>
#include <iostream>

Simulator::Simulator(const std::shared_ptr<const Scenario> scenario)
    : _scenario(scenario), _statistics(std::make_shared<Statistics>(scenario)),
      _clock(std::make_shared<Clock>()),
      _eventQueue(std::make_shared<EventQueue>()),
      _eventDispatcher(std::make_shared<EventDispatcher>()) {
  auto seed = scenario->getSeed();
  std::seed_seq seed_seq(seed.begin(), seed.end());
  _random_engine = std::shared_ptr<std::mt19937>(new std::mt19937(seed_seq));

  google::SetLogDestination(google::INFO, _scenario->getPath().c_str());
}

Simulator::Simulator(const Simulator &simulator)
    : _scenario(std::make_shared<Scenario>(*simulator.getScenario())),
      _statistics(std::make_shared<Statistics>(_scenario)),
      _clock(std::make_shared<Clock>(*simulator.getClock())),
      _eventQueue(std::make_shared<EventQueue>()),
      _eventDispatcher(std::make_shared<EventDispatcher>()) {}

Simulator::~Simulator() {}

std::shared_ptr<Building> Simulator::createBuilding() const {
  auto floors = Floor::create(shared_from_this());
  auto elevators = Elevator::create(shared_from_this());
  auto scheduler = SchedulerCreator::create(_scenario->getSchedulerType());
  auto costFunction = CostFunctionCreator::create(_scenario->getCostFunctionType());

  auto building = std::make_shared<Building>(shared_from_this(), _clock, floors, elevators, scheduler, costFunction);

  LOG(INFO) << "Created '" << _scenario->getName() << "' scenario with "
            << floors->size() << " floors, "
            << elevators->size() << " elevators, '"
            << Helpers::schedulerName(_scenario->getSchedulerType()) << "' scheduler and '"
            << Helpers::costFunctionName(_scenario->getCostFunctionType())
            << "' cost function.";

  return building;
}

void Simulator::copyBuilding(const Building& building) {
  _building = std::make_shared<Building>(building, shared_from_this(), _clock);
}

const std::shared_ptr<Building> Simulator::getBuilding() const { return _building; }

const std::shared_ptr<const Scenario> Simulator::getScenario() const { return _scenario; }

const std::shared_ptr<Statistics> Simulator::getStatistics() const { return _statistics; }

const std::shared_ptr<Clock> Simulator::getClock() const { return _clock; }

const std::shared_ptr<EventQueue> Simulator::getEventQueue() const { return _eventQueue; }

const std::shared_ptr<EventDispatcher> Simulator::getEventDispatcher() const { return _eventDispatcher; }

const std::shared_ptr<std::mt19937> Simulator::getRandomEngine() const { return _random_engine; }

void Simulator::run() {
  std::cout << "Simulating '" << _scenario->getName() << "' scenario with '"
      << Helpers::schedulerName(_scenario->getSchedulerType()) << "' scheduler and '"
      << Helpers::costFunctionName(_scenario->getCostFunctionType())
      << "' cost function... ";

  std::cout.flush();
  Client::resetIds();

  _building = createBuilding();
  _building->initializeArrivals();

  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_building));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_clock));
  _eventDispatcher->subscribe(std::static_pointer_cast<EventObserver>(_statistics));

  auto finishSimulationEvent = std::make_shared<FinishSimulation>(_scenario->getDuration());
  _eventQueue->push(std::static_pointer_cast<Event>(finishSimulationEvent));

  while (_statistics->keepRunning() && _eventQueue->hasNextEvent()) {
    auto e = _eventQueue->pop();
    if (e) {
      _eventDispatcher->broadcast(e);
      _eventQueue->refresh(_clock->currentTime());
    }
  }

  std::cout << "done!" << std::endl;
  std::cout.flush();
}

bool Simulator::nextStep() { return true; }
