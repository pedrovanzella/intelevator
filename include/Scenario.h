#pragma once

#include <ctime>
#include <memory>
#include <string>
#include <vector>

namespace YAML { class Node; } // forward declaration
enum class CostFunctionType;   // forward declaration
enum class SchedulerType;      // forward declaration

class Scenario {
public:
  Scenario(const int seq, std::string name, int duration, int elevatorCount, int capacity,
           int floorCount, SchedulerType schedulerType,
           CostFunctionType costFunctionType, std::string seed,
           std::vector<float> floors, std::time_t timestamp,
           int planningHorizon);
  Scenario(const Scenario& scenario);
  virtual ~Scenario();

  static std::shared_ptr<std::vector<std::shared_ptr<const Scenario>>> Load(std::string file);

  const int getSeq() const;
  const std::string getName() const;
  const int getDuration() const;
  const int getElevatorCount() const;
  const int getCapacity() const;
  const int getFloorCount() const;
  const int getPlanningHorizon() const;
  const SchedulerType getSchedulerType() const;
  const CostFunctionType getCostFunctionType() const;
  const std::vector<float> getFloors() const;
  const std::string getSeed() const;
  const std::time_t getTimestamp() const;
  const std::string getBasePath() const;
  const std::string getPath() const;

private:
  const int _seq;
  const std::string _name;
  const int _duration;
  const int _elevatorCount;
  const int _capacity;
  const int _floorCount;
  const SchedulerType _schedulerType;
  const CostFunctionType _costFunctionType;
  const std::string _seed;
  std::vector<float> _floors;
  std::time_t _timestamp;
  const int _planningHorizon;
};
