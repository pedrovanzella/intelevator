#pragma once

#include <ctime>
#include <memory>
#include <random>

class Clock;           // forward declaration
class Building;        // forward declaration
class Statistics;      // forward declaration
class EventQueue;      // forward declaration
class EventDispatcher; // forward declaration
class Scenario;        // forward declaration

class Simulator : public std::enable_shared_from_this<Simulator> {
public:
  Simulator(std::shared_ptr<const Scenario> scenario);
  virtual ~Simulator();

  std::shared_ptr<Building> createBuilding() const;

  const std::shared_ptr<const Scenario> getScenario() const;
  const std::shared_ptr<Statistics> getStatistics() const;
  const std::shared_ptr<Clock> getClock() const;
  const std::shared_ptr<EventQueue> getEventQueue() const;
  const std::shared_ptr<EventDispatcher> getEventDispatcher() const;
  const std::shared_ptr<std::default_random_engine> getRandomEngine() const;

  const std::string getPath() const;

  void run();

private:
  const std::shared_ptr<const Scenario> _scenario;
  const std::shared_ptr<Statistics> _statistics;
  const std::shared_ptr<Clock> _clock;
  const std::shared_ptr<EventQueue> _eventQueue;
  const std::shared_ptr<EventDispatcher> _eventDispatcher;
  std::shared_ptr<std::default_random_engine> _random_engine;

  std::shared_ptr<Building> _building;
  std::time_t _startedAt;

  bool nextStep();
};
