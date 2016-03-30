#pragma once

#include <map>
#include <sstream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "Property.h"

class Config
{
public:
  Config(const std::string file);
  virtual ~Config();

  static std::string getPropName (Property p);

  int getInt(Property property) const;
  float getFloat(Property property) const;
  std::string getString(Property property) const;

  void setInt(Property property, int value);
  void setFloat(Property property, float value);
  void setString(Property property, std::string value);

private:
  std::map<Property, int> intProps;
  std::map<Property, float> floatProps;
  std::map<Property, std::string> stringProps;
};
