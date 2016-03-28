#include <stdexcept>
#include <iostream>
#include "Config.h"
#include "easylogging++.h"

Config::Config()
{
  LOG(TRACE) << "Config created.";
}

Config::~Config()
{
  LOG(TRACE) << "Config destroyed.";
}

std::string Config::getPropName (Property p)
{
  const std::map<Property, const std::string> PropertyStrings
  {
    { Property::Title, "Property::Title" },
    { Property::Floors, "Property::Floors" },
    { Property::Elevators, "Property::Elevators" },
    { Property::MaxLoad, "Property::MaxLoad" },
    { Property::Duration, "Property::Duration" },
    { Property::Dispatcher, "Property::Dispatcher" },
    { Property::CostFunction, "Property::CostFunction" },
    { Property::Seed, "Property::Seed" },
    { Property::Mean, "Property::Mean" },
    { Property::Deviation, "Property::Deviation" }
  };

  auto it = PropertyStrings.find(p);
  return it == PropertyStrings.end() ? "Out of range" : it->second;
}

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

int Config::getInt(Property property) const
{
  auto it = intProps.find(property);
  if (it == intProps.end())
    throw std::invalid_argument("Can't find " + getPropName(property) + ".");

  return it->second;
}

float Config::getFloat(Property property) const
{
  auto it = floatProps.find(property);
  if (it == floatProps.end())
    throw std::invalid_argument("Can't find " + getPropName(property) + ".");

  return it->second;
}

std::string Config::getString(Property property) const
{
  auto it = stringProps.find(property);
  if (it == stringProps.end())
    throw std::invalid_argument("Can't find " + getPropName(property) + ".");

  return it->second;
}

void Config::setInt(Property property, int value)
{
  intProps[property] = value;
}

void Config::setFloat(Property property, float value)
{
  floatProps[property] = value;
}

void Config::setString(Property property, std::string value)
{
  stringProps[property] = value;
}

void Config::storeLine(std::string key, std::string value)
{
  if (key == "title") {
    setString(Property::Title, value);
  }
  else if (key == "floors") {
    setInt(Property::Floors, std::stoi(value));
  }
  else if (key == "elevators") {
    setInt(Property::Elevators, std::stoi(value));
  }
  else if (key == "maxLoad") {
    setInt(Property::MaxLoad, std::stoi(value));
  }
  else if (key == "duration") {
    setFloat(Property::Duration, std::stoi(value));
  }
  else if (key == "dispatcher") {
    setString(Property::Dispatcher, value);
  }
  else if (key == "costFunction") {
    setString(Property::CostFunction, value);
  }
  else if (key == "seed")
  {
    setInt(Property::Seed, std::stoi(value));
  }
  else if (key == "mean")
  {
    setFloat(Property::Mean, std::stof(value));
  }
  else if (key == "deviation")
  {
    setFloat(Property::Deviation, std::stof(value));
  }
  else
  {
    throw std::invalid_argument("Invalid key: " + key);
  }
}
