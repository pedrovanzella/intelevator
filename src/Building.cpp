#include "Building.h"
#include "Client.h"
#include "ClientArrival.h"
#include "Clock.h"
#include "CostFunction.h"
#include "Direction.h"
#include "Dispatcher.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "Floor.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Status.h"
#include "StopManager.h"
#include "Trip.h"
#include <algorithm>
#include <glog/logging.h>
#include <sstream>

Building::Building(
    std::shared_ptr<const Simulator> simulator,
    std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
    std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
    std::shared_ptr<Dispatcher> dispatcher,
    std::shared_ptr<const CostFunction> costFunction)
    : _simulator(simulator), _clock(_simulator->getClock()), _floors(floors),
      _elevators(elevators), _dispatcher(dispatcher),
      _costFunction(costFunction), _stops(), _stopManager(new StopManager()) {}

Building::~Building() {}

const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Building::getElevators() const { return _elevators; }

const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> Building::getFloors() const { return _floors; }

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

  for (int time = _clock->currentTime(); time < event->getTime(); ++time) {
    _clock->advanceBy(1);
    for (auto elevator : *_elevators) {
      updateElevator(elevator);
    }
  }

  /*
    Após a atualização do estado do sistema, o novo evento deve ser processado
    e o sistema deverá atualizar o seu estado de acordo com esse evento.
  */
  if (event->getType() == EventType::clientArrival) {
    LOG(INFO) << event->str();
    doClientArrival(std::static_pointer_cast<const ClientArrival>(event));
  }

  if (event->getType() == EventType::finishSimulation) {
    int clientsOnLines = 0;
    for (auto floor : *_floors) {
      clientsOnLines += floor->clientsOnDownLine() + floor->clientsOnUpLine();
    }

    int clientsOnElevators = 0;
    for (auto elevator : *_elevators) {
      clientsOnElevators += elevator->getPassengers()->size();
    }

    LOG(INFO) << "A total of " << clientsOnLines << " clients remains on lines.";
    LOG(INFO) << "A total of " << clientsOnElevators << " clients remains inside elevators.";
  }
}

void Building::initializeArrivals() {
  for (auto floor : *_floors)
    floor->createFutureArrival(_simulator->getEventQueue());
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
  auto direction = location->addClient(client);

  auto currentElevator = _stopManager->get(location, direction);
  if (currentElevator == nullptr) {
    auto elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), event);
    auto elevator = _elevators->at(elevatorNum);
    _stopManager->set(location, direction, elevator);
    // LOG(INFO) << "Elevator #" << elevator->getNumber()
    //           << " was assigned to stop at floor #" << location->getNumber()
    //           << " to go " << Helpers::directionName(direction) << " (" << _clock->str() << ").";
  }

  location->createFutureArrival(_simulator->getEventQueue());
}

void Building::updateElevator(const std::shared_ptr<Elevator> elevator) {
  if (elevator->getStatus() == Status::Idle) {
    elevator->setDestination(getDestinationForElevator(elevator));
  }

  elevator->move();
  if (mustStop(elevator)) {
    stop(elevator);

    auto droppedPassengers = elevator->dropPassengersToCurrentLocation();
    auto stats = _simulator->getStatistics();
    stats->logDropOff(_clock->currentTime(), elevator, droppedPassengers);

    auto floor = _floors->at(elevator->getLocation());
    auto newStops = floor->boardElevator(_clock->currentTime(), elevator);
    registerNewStops(elevator, newStops);
  }
}

std::pair<int, Direction> Building::getDestinationForElevator(const std::shared_ptr<Elevator> elevator) {
  // LOG(INFO) << "GONNA GET NEW DEST";
  auto up = _stopManager->getStops(elevator, Direction::Up);
  auto down = _stopManager->getStops(elevator, Direction::Down);

  switch (elevator->getDirection()) {
  case Direction::Up:
    if (down.empty()) { // cant' go down
      if (up.empty()) // can't go up
        return { elevator->getLocation(), Direction::Up }; // don't move
      else // can go up
        return { (*up.rbegin())->getNumber(), Direction::Up }; // go up
    } else { // can go down
      return { (*down.begin())->getNumber(), Direction::Down }; // go down
    }
    break;

  case Direction::Down:
    if (up.empty()) { // cant' go up
      if (down.empty()) // can't go down
        return { elevator->getLocation(), Direction::Up }; // don't move
      else // can go down
        return { (*down.begin())->getNumber(), Direction::Down }; // go down
    } else { // can go up
      return { (*up.rbegin())->getNumber(), Direction::Up }; // go up
    }
    break;
  }
}

bool Building::mustStop(const std::shared_ptr<Elevator> elevator) {
  auto location = _floors->at(elevator->getLocation());

  auto stops = _stopManager->getStops(elevator, elevator->getDestination().second);
  if (stops.find(location) != stops.end()) return true;

  return false;
}

void Building::stop(const std::shared_ptr<Elevator> elevator) {
  auto location = _floors->at(elevator->getLocation());
  _stopManager->clear(location, elevator->getDestination().second);
  // LOG(INFO) << "Elevator #" << elevator->getNumber()
  //           << " stopped at floor #" << elevator->getLocation()
  //           << " (" << _clock->str() << ").";
}

void Building::registerNewStops(std::shared_ptr<Elevator> elevator, std::set<int> stops) {
  for (auto floorNumber : stops) {
    auto location = _floors->at(elevator->getLocation());
    auto destination = _floors->at(floorNumber);
    _stopManager->set(destination, location->compareTo(*destination), elevator);
  }
}