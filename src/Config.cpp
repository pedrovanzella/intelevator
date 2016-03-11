#include "Config.h"
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>

Config::Config() {}

Config::~Config() {}

void Config::from_file(std::istringstream &is_file)
{
  if (is_file.bad()) {
    throw std::invalid_argument("Invalid File");
  }

  std::string line;

  while (std::getline(is_file, line)) {
    std::istringstream is_line(line);
    std::string key;

    if(std::getline(is_line, key, '=')) {
      std::string value;

      if(std::getline(is_line, value)) {
        store_line(key, value);
      }
    }
  }
}

void Config::store_line(std::string key, std::string value)
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
