#include "Floor.h"

Floor::Floor(const Building& building, int number)
 : building(building)
 , number(number) {}

Floor::~Floor()
{}

const Building& Floor::getBuilding()
{
  return this->building;
}

int Floor::getNumber()
{
  return this->number;
}

void Floor::notify(const Event& event)
{
  // Handle events
}