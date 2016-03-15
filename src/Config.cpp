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
    floors = std::stoi(value);
    return;
  }
  if (key == "elevators") {
    elevators = std::stoi(value);
    return;
  }
  if (key == "maxLoad") {
    maxLoad = std::stoi(value);
    return;
  }
  if (key == "duration") {
    duration = std::stof(value);
    return;
  }
  if (key == "title") {
    title = value;
    return;
  }
  if (key == "seed") {
    seed = std::stoi(value);
    return;
  }
  throw std::invalid_argument("Invalid key");
}
