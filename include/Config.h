#pragma once

#include <string>

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

  void from_file(std::string filename);

private:
  void store_line(std::string key, std::string value);
};
