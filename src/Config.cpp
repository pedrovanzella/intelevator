#include "Config.h"
#include <sstream>
#include <stdexcept>
#include <string>

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
    if(std::getline(is_line, key, '='))
      {
        std::string value;
        if(std::getline(is_line, value)) 
          store_line(key, value);
      }
  }
}

void Config::store_line(std::string key, std::string value)
{
  // We can't use a switch with std::strings, apparently
  if (key == "floors") {
    this->floors = std::stoi(value);
    return;
  }
  if (key == "elevators") {
    this->elevators = std::stoi(value);
    return;
  }
  if (key == "maxLoad") {
    this->maxLoad = std::stoi(value);
    return;
  }
  if (key == "duration") {
    this->duration = std::stof(value);
    return;
  }
  if (key == "title") {
    this->title = value;
    return;
  }
  if (key == "seed") {
    this->seed = std::stoi(value);
    return;
  }
  throw std::invalid_argument("Invalid key");
}
