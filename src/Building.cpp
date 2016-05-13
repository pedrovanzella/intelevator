#include "Building.h"
#include "ClientArrival.h"
#include "CostFunction.h"
#include "Dispatcher.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "Floor.h"
#include "Simulator.h"
#include "Trip.h"
#include <algorithm>
#include <glog/logging.h>
#include <sstream>

Building::Building(
    std::shared_ptr<Simulator> simulator,
    std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
    std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
    std::shared_ptr<Dispatcher> dispatcher,
    std::shared_ptr<const CostFunction> costFunction)
    : _simulator(simulator), _floors(floors), _elevators(elevators),
      _dispatcher(dispatcher), _costFunction(costFunction), _stops(),
      _lastEventTime(0) {}

Building::~Building() {}

const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Building::getElevators() const {
  return _elevators;
}

const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> Building::getFloors() const {
  return _floors;
}

const std::shared_ptr<Floor> Building::getFloor(int number) const {
  if (number >= _floors->size())
    throw std::out_of_range("Floor number out of range: " + std::to_string(number));
  return _floors->at(number);
}

const std::shared_ptr<Elevator> Building::getElevator(int number) const {
  if (number >= _elevators->size())
    throw std::out_of_range("Elevator number our of range: " + std::to_string(number));
  return _elevators->at(number);
}

void Building::notify(const std::shared_ptr<const Event> event) {
  /*
    Ao ser notificado de um evento, o sistema deve atualizar o seu estado para
    refletir o que ocorreu no interim entre o momento do último evento
    processado e o evento que está sendo notificado.
  */

  for (int time = _lastEventTime; time < event->getTime(); ++time) {
    updateElevators(time);
  }

  LOG(INFO) << event->str();

  /*
    Após a atualização do estado do sistema, o novo evento deve ser processado
    e o sistema deverá atualizar o seu estado de acordo com esse evento.
  */
  if (event->getType() == EventType::clientArrival) {
    doClientArrival(std::static_pointer_cast<const ClientArrival>(event));
    createFutureArrival();
  }

  /*
    E depois salvar o tempo do último evento processo - e, não por coincidência,
    este tempo é o valor do relógio de simulação atual.
  */
  _lastEventTime = event->getTime();
}

void Building::createFutureArrival() {
  // for (auto floor : *_floors)
  //   floor->createFutureArrival(_simulator->getEventQueue());
}

void Building::doClientArrival(std::shared_ptr<const ClientArrival> event) {
  /*
    Um evento ClientArrival ocorre em um andar específico. O Building deve
    localizar o Floor correspondente e notificá-lo da chegada deste novo
    cliente.

    O cliente (carregando suas informações) entrará em uma das filas daquele
    andar. No mundo real, se o cliente chega em uma das filas (de subida ou de
    descida) e não há ninguém na fila, ele aperta o botão do sentido que
    deseja ir.
  */
  auto client = event->getClient();
  auto location = _floors->at(client->getArrivalFloor());
  location->addClient(client);

  /*
    O sistema, ao perceber que um novo botão foi pressionado, designa um
    elevador para atender aquela nova requisição.
  */
    auto elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), event);
    auto elevator = _elevators->at(elevatorNum);

  /* Agora, esse elevador deve parar no andar em que ocorreu o evento para buscar a pessoa. */

  if (_stops[elevator].find(client->getArrivalFloor()) == _stops[elevator].end()) {
    _stops[elevator].insert(client->getArrivalFloor());
    // LOG(INFO) << "Elevator #" << elevator->getNumber()
    //           << " will stop on floor " << client->getArrivalFloor()
    //           << " to pick up some clients.";
  }
}

void Building::updateElevators(const unsigned long time) {
  for (auto elevator : *_elevators) {
    assignDestinationForElevator(elevator);

    if (!mustStopAtNextLocation(elevator)) {
      elevator->goToNextLocation();
      continue;
    }

    elevator->mustStopAtNextLocation();
    elevator->goToNextLocation();
    _stops[elevator].erase(elevator->getLocation());

    LOG(INFO) << "Elevator #" << elevator->getNumber()
              << " stopped at floor #" << elevator->getLocation() << " (t=" << time << ").";

    auto droppedPassengers = elevator->dropPassengersToCurrentLocation();
    auto stats = _simulator->getStatistics();
    stats->logDropOff(time, elevator, droppedPassengers);

    auto floor = _floors->at(elevator->getLocation());
    auto newStops = floor->boardElevator(elevator);
    registerNewStops(elevator, newStops);
  }
}

void Building::assignDestinationForElevator(const std::shared_ptr<Elevator> elevator) {
  if (elevator->getStatus() == Status::Idle && !_stops[elevator].empty()) {
    // If an elevator is idle and has pending stops, then it should receive a new destination.
    if (elevator->getDirection() == Direction::Up) {
      // If it was going up, we send it down.
      elevator->setDestination(*_stops[elevator].begin());
    }
    else {
      // If it was going down, we send it up.
      elevator->setDestination(*_stops[elevator].rbegin());
    }
  }
}

bool Building::mustStopAtNextLocation(const std::shared_ptr<Elevator> elevator) {
  auto nextLocation = elevator->getNextLocation();
  return _stops[elevator].find(nextLocation) != _stops[elevator].end();
}

void Building::registerNewStops(std::shared_ptr<Elevator> elevator, std::set<int> stops) {
  for (auto stop : stops) {
    _stops[elevator].insert(stop);
  }
}
