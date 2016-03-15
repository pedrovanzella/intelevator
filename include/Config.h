#pragma once

#include <string>
#include <sstream>

class Config {
public:
  int _floors;
  int _elevators;
  int _maxLoad;
  float _duration;
  std::string _title;
  int _seed;

  Config();
  virtual ~Config();

  void fromFile(std::istringstream& isFile);

private:
  void storeLine(std::string key, std::string value);
};
