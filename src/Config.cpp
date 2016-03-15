#include <stdexcept>
#include <iostream>
#include "Config.h"

Config::Config() {}

Config::~Config() {}

void Config::fromFile(std::istringstream& isFile)
{
  if (isFile.bad()) {
    throw std::invalid_argument("Invalid File");
  }

  std::string line;

  while (std::getline(isFile, line)) {
    std::istringstream is_line(line);
    std::string key;

    if(std::getline(is_line, key, '=')) {
      std::string value;

      if(std::getline(is_line, value)) {
        storeLine(key, value);
      }
    }
  }
}

void Config::storeLine(std::string key, std::string value)
{
  // We can't use a switch with std::strings, apparently
  if (key == "floors") {
    _floors = std::stoi(value);
    return;
  }
  if (key == "elevators") {
    _elevators = std::stoi(value);
    return;
  }
  if (key == "maxLoad") {
    _maxLoad = std::stoi(value);
    return;
  }
  if (key == "duration") {
    _duration = std::stof(value);
    return;
  }
  if (key == "title") {
    _title = value;
    return;
  }
  if (key == "seed") {
    _seed = std::stoi(value);
    return;
  }
  throw std::invalid_argument("Invalid key");
}
