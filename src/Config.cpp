#include <stdexcept>
#include <iostream>
#include "Config.h"
#include "easylogging++.h"

Config::Config(const std::string file)
{
  YAML::Node config = YAML::LoadFile(file);

  setString(Property::Title, config["simulation"]["title"].as<std::string>());
  setInt(Property::Duration, config["simulation"]["duration"].as<int>());

  setInt(Property::Floors, config["building"]["floors"].as<int>());
  setInt(Property::Elevators, config["building"]["elevators"].as<int>());
  setInt(Property::MaxLoad, config["building"]["max_load"].as<int>());

  setString(Property::Dispatcher, config["dispatcher"]["name"].as<std::string>());
  setString(Property::CostFunction, config["dispatcher"]["cost_function"].as<std::string>());

  setString(Property::PoissonSeed, config["poisson"]["seed"].as<std::string>());
  setInt(Property::Population, config["poisson"]["population"].as<int>());
  setInt(Property::EventInterval, config["poisson"]["event_interval"].as<int>());
  setInt(Property::Experiments, config["poisson"]["experiments"].as<int>());

  LOG(INFO) << "Configuration loaded from '" << file << "'.";
}

Config::~Config()
{}

std::string Config::getPropName (Property p)
{
  const std::map<Property, const std::string> PropertyStrings
  {
    { Property::Title, "Property::Title" },
    { Property::Duration, "Property::Duration" },
    { Property::Floors, "Property::Floors" },
    { Property::Elevators, "Property::Elevators" },
    { Property::MaxLoad, "Property::MaxLoad" },
    { Property::Duration, "Property::Duration" },
    { Property::Dispatcher, "Property::Dispatcher" },
    { Property::CostFunction, "Property::CostFunction" },
    { Property::PoissonSeed, "Property::PoissonSeed" },
    { Property::Population, "Property::Population" },
    { Property::EventInterval, "Property::EventInterval" },
    { Property::Experiments, "Property::Experiments" }
  };

  auto it = PropertyStrings.find(p);
  return it == PropertyStrings.end() ? "Out of range" : it->second;
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
