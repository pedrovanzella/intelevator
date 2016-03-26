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

void Config::setTitle(const std::string title)
{
  _title = title;
}

void Config::setSeed(const int seed)
{
  _seed = seed;
}

void Config::setFloors(const int floors)
{
  _floors = floors;
}

void Config::setElevators(const int elevators)
{
  _elevators = elevators;
}

void Config::setMaxLoad(const int maxLoad)
{
  _maxLoad = maxLoad;
}

void Config::setDuration(const int duration)
{
  _duration = duration;
}

void Config::setDispatcher(const std::string dispatcher) {
  _dispatcher = dispatcher;
}

void Config::setCostFunction(const std::string costFunction)
{
  _costFunction = costFunction;
}

std::string Config::getTitle() const
{
  return _title;
}

int Config::getSeed() const
{
  return _seed;
}

int Config::getFloors() const
{
  return _floors;
}

int Config::getElevators() const
{
  return _elevators;
}

int Config::getMaxLoad() const
{
  return _maxLoad;
}

float Config::getDuration() const
{
  return _duration;
}

std::string Config::getDispatcher() const {
  return _dispatcher;
}

std::string Config::getCostFunction() const
{
  return _costFunction;
}

void Config::storeLine(std::string key, std::string value)
{
  // We can't use a switch with std::strings, apparently
  if (key == "title") {
    setTitle(value);
  }
  else if (key == "seed") {
    setSeed(std::stoi(value));
  }
  else if (key == "floors") {
    setFloors(std::stoi(value));
  }
  else if (key == "elevators") {
    setElevators(std::stoi(value));
  }
  else if (key == "maxLoad") {
    setMaxLoad(std::stoi(value));
  }
  else if (key == "duration") {
    setDuration(std::stof(value));
  }
  else
  {
    throw std::invalid_argument("Invalid key: " + key);
  }
}


