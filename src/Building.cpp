#include <algorithm>
#include <iostream>
#include <memory>

#include "Building.h"
#include <glog/logging.h>
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
    auto ce = std::static_pointer_cast<const ClientArrival>(event);

    /*
      Um evento ClientArrival ocorre em um andar específico. O Building deve
      localizar o Floor correspondente e notificá-lo da chegada deste novo
      cliente.
    */

    auto location = _floors->at(ce->getLocation());

    /*
      O cliente (carregando suas informações) entrará em uma das filas daquele
      andar. No mundo real, se o cliente chega em uma das filas (de subida ou de
      descida) e não há ninguém na fila, ele aperta o botão do sentido que
      deseja ir.

      O sistema, ao perceber que um novo botão foi pressionado, designa um
      elevador para atender aquela nova requisição.
    */

    bool hasUpCall = location->hasUpCall();
    bool hasDownCall = location->hasDownCall();

    location->addClient(ce->getClient());

    bool hasUpCallAfter = location->hasUpCall();
    bool hasDownCallAfter = location->hasDownCall();

    if (!hasUpCall && hasUpCallAfter)
    {
      /*
        Antes não tinha ninguém pra subir; agora, tem.
        O dispatcher recebe esta informação e devolve o número do elevator
        que deverá atender esta solicitação.
      */

      int elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), ce);
      auto elevator = _elevators->at(elevatorNum);

      /*
        Agora, existem algus casos que podem ocorrer:

          1) Este elevador está parado (ou seja, não tem nada pra atender);
          2) Este elevador está em movimento, atendendo um chamado, mas não tem mais parada pra fazer depois;
          3) Este elevador está em movimento, atendendo um chamado, e tem mais paradas pra fazer depois.

          Como tratar?

            Possibilidade 1: para cada elevador, guardar dentro do Building uma lista (ou outra estrutura mais
                             apropriada) que irá armazenar as paradas que o elevador deverá realizar, na ordem
                             em que elas devem ocorrer. Quando o elevador chega em um destino, o Building irá
                             retirar o próximo destino da lista armazenada e irá entregar para o elevador, que
                             continuará sua viagem através do prédio. Quando o elevador não possui mais paradas
                             para realizar, ele fica parado (futuramente podemos adicionar heurísticas neste
                             caso).

            Possibilidade 2: sei lá.
      */
    }

    if (!hasDownCall && hasDownCallAfter)
    {
      /*
        Antes não tinha ninguém pra descer; agora, tem.
        O dispatcher recebe esta informação e devolve o número do elevator
        que deverá atender esta solicitação.
      */

      int elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), ce);
      auto elevator = _elevators->at(elevatorNum);

      /*
        ... (mesmo caso que o acima)
      */
    }
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
