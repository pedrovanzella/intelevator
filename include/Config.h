#pragma once

#include <string>

class Config {
public:
  int floors;
  int elevators;
  int maxLoad;
  float duration;
  std::string title;

  Config();
  virtual ~Config();
};