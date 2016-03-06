#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

class Config {
public:
  int floors;
  int elevators;
  int maxLoad;
  float simulatorDuration;
  std::string title;
};

#endif /* _CONFIG_H_ */
