#include <algorithm>
#include <iostream>
#include <memory>

#include "Building.h"
#include "easylogging++.h"
#include "Elevator.h"
#include "Floor.h"

Building::Building(std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
                   std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
                   std::shared_ptr<const Dispatcher> dispatcher,
                   std::shared_ptr<const CostFunction> costFunction)
  : _floors(floors)
  , _elevators(elevators)
  , _dispatcher(dispatcher)
  , _costFunction(costFunction)
{}

Building::~Building() {}

void Building::notify(const std::shared_ptr<const Event> event)
{
  LOG(INFO) << "Building reacting to event " << event->str() << ".";

  if (event->getType() == EventType::clientArrival)
  {
    /*
      Quando ocorre um clientArrival, ele ocorre em um andar específico.
      O Building deve decidir se esse clientArrival é pra subir ou é pra descer e colocar na fila correta do andar específico.
      Além disso, deve saber se já tem chamada para subir ou para descer neste andar.
    */
    auto ce = std::static_pointer_cast<const ClientArrival>(event);

    int elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), ce);
    LOG(INFO) << "Dispatcher has chosen elevator #" << elevatorNum << ".";

    auto e = _elevators->at(elevatorNum);
    LOG(INFO) << "Currently, elevator " << e->getNumber() << " is " << Helpers::elevatorStatusName(e->getStatus()) << ".";

    e->setDestination(ce->getClient()->getDestination());
  }
  // TO-DO
}

const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Building::getElevators() const
{
  return _elevators;
}

const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> Building::getFloors() const
{
  return _floors;
}

const std::shared_ptr<Floor> Building::getFloor(int number) const
{
  if (number >= _floors->size()) throw std::out_of_range ("Floor number out of range: " + std::to_string(number));
  return _floors->at(number);
}

const std::shared_ptr<Elevator> Building::getElevator(int number) const
{
  if (number >= _elevators->size()) throw std::out_of_range ("Elevator number our of range: " + std::to_string(number));
  return _elevators->at(number);
}
