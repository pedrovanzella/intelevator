#pragma once

#include <memory>
#include <string>

class Scenario;        // forward declaration
class Simulator;       // forward declaration
class Statistics;      // forward declaration

class Reporter {
public:
  Reporter(std::shared_ptr<Simulator> simulator);
  virtual ~Reporter();

  void generateReport();
  void generateArrivals();
  void generateDropOffs();
  void generateCharts();

private:
  const std::string _outputPath;
  const std::shared_ptr<const Scenario> _scenario;
  const std::shared_ptr<Statistics> _statistics;
};
