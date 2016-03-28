#pragma once

#include <map>
#include <sstream>
#include <string>

#include "Property.h"

class Config
{
public:
  Config();
  virtual ~Config();

  static std::string getPropName (Property p);
  void fromFile(std::istringstream& isFile);

  int getInt(Property property) const;
  float getFloat(Property property) const;
  std::string getString(Property property) const;

  void setInt(Property property, int value);
  void setFloat(Property property, float value);
  void setString(Property property, std::string value);

private:
  void storeLine(std::string key, std::string value);

  std::map<Property, int> intProps;
  std::map<Property, float> floatProps;
  std::map<Property, std::string> stringProps;
};
