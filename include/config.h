#pragma once

#include <string>

class Config {
public:
  int floors;
  int elevators;
  int maxLoad;
  float simulatorDuration;
  std::string title;
};