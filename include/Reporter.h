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

  void add(std::shared_ptr<Statistics> statistics);

  void generate();

  void generateUnifiedReport(std::vector<std::shared_ptr<Statistics>> stats);
  void generateReport(std::shared_ptr<Statistics> statistics);
  void generateArrivals(std::shared_ptr<Statistics> statistics);
  void generateDropOffs(std::shared_ptr<Statistics> statistics);
  void generateCharts();

private:
  std::map<std::string, std::vector<std::shared_ptr<Statistics>>> _stats;
};