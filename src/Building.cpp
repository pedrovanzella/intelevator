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
      Um evento ClientArrival ocorre em um andar específico.  O Building deve
      localizar o Floor correspondente e notificá-lo da chegada deste novo
      cliente.
    */
    auto ce = std::static_pointer_cast<const ClientArrival>(event);
    auto location = _floors->at(ce->getLocation());
    location->addClient(ce->getClient());

    /*
      A partir deste ponto, o cliente (carregando suas informações) está em uma
      das filas daquele andar. No mundo real, se o cliente chega em uma das
      filas (de subida ou de descida) e não houver ninguém na fila, ele apertará
      o botão do sentido que deseja ir.

      O sistema, ao perceber que um novo botão foi pressionado, deve designar
      um elevator para atender aquele request.
    */
  }
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
