#pragma once

#include <string>
#include <sstream>

class Config {
public:
  Config();
  virtual ~Config();

  void fromFile(std::istringstream& isFile);

  void setTitle(const std::string title);
  void setSeed(const int seed);
  void setFloors(const int floors);
  void setElevators(const int elevators);
  void setMaxLoad(const int maxLoad);
  void setDuration(const int duration);
    void setDispatcher(const std::string dispatcher);
    void setCostFunction(const std::string costFunction);

  std::string getTitle() const;
  int getSeed() const;
  int getFloors() const;
  int getElevators() const;
  int getMaxLoad() const;
  float getDuration() const;
    std::string getDispatcher() const;
    std::string getCostFunction() const;

private:
  int _floors;
  int _elevators;
  int _maxLoad;
  float _duration;
  std::string _title;
  int _seed;
    std::string _dispatcher;
    std::string _costFunction;

  void storeLine(std::string key, std::string value);
};
