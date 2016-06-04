#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

class Scenario;        // forward declaration
class Simulator;       // forward declaration
class Statistics;      // forward declaration

class Reporter {
public:
  Reporter();
  virtual ~Reporter();

  void generate(std::shared_ptr<Simulator> simulator);
  void generate();

  void generateUnifiedReport(std::vector<std::shared_ptr<Simulator>> simulators);
  void generateReport(std::shared_ptr<Simulator> simulator);
  void generateArrivals(std::shared_ptr<Simulator> simulator);
  void generateDropOffs(std::shared_ptr<Simulator> simulator);
  void generateCharts(std::shared_ptr<Simulator> simulator);

private:
  std::map<std::string, std::vector<std::shared_ptr<Simulator>>> _simulators;
};