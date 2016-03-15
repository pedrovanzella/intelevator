#pragma once

#include <string>
#include <sstream>

class Config {
public:
  int floors;
  int elevators;
  int maxLoad;
  float duration;
  std::string title;
  int seed;

  Config();
  virtual ~Config();

  void fromFile(std::istringstream& isFile);

private:
  void storeLine(std::string key, std::string value);
};
