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

  void generateReport();
  void generateArrivals(const std::string path, std::shared_ptr<Statistics> statistics);
  void generateDropOffs(const std::string path, std::shared_ptr<Statistics> statistics);
  void generateCharts();

private:
  std::map<std::string, std::vector<std::shared_ptr<Statistics>>> _stats;
  // const std::string _outputPath;
  // const std::shared_ptr<const Scenario> _scenario;
  // const std::shared_ptr<Statistics> _statistics;
};

/*

output / group1_TIMESTAMP / report.log
                          / scenario1 / intelevator.INFO
                                      / trips.log
                                      / arrivals.log
          
                          / scenario2 / intelevator.INFO
                                      / trips.log
                                      / arrivals.log

*/