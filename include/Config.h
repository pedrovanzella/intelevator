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

  void from_file(std::istringstream &is_file);

private:
  void store_line(std::string key, std::string value);
};
