#include "Building.h"
#include "Elevator.h"
#include "Floor.h"
#include "Trip.h"
#include "Simulator.h"
#include <algorithm>
#include <glog/logging.h>
#include <sstream>

Building::Building(
  std::shared_ptr<Simulator> simulator,
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
  std::shared_ptr<const Dispatcher> dispatcher,
  std::shared_ptr<const CostFunction> costFunction)
  : _simulator(simulator), _floors(floors), _elevators(elevators), _dispatcher(dispatcher),
    _costFunction(costFunction), _stops(), _lastEventTime(0) {}

Building::~Building() {}

void Building::notify(const std::shared_ptr<const Event> event) {
  for (int time = _lastEventTime; time < event->getTime(); ++time) {
    updateElevators(time);
  }

  if (event->getType() == EventType::clientArrival) {
    doClientArrival(std::static_pointer_cast<const ClientArrival>(event));
  }

  _lastEventTime = event->getTime();
}

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

  int elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), event);

  /* Agora, esse elevador deve parar no andar em que ocorreu o evento para buscar a pessoa. */

  if (_stops[elevatorNum].find(client->getArrivalFloor()) == _stops[elevatorNum].end()) {
    _stops[elevatorNum].insert(client->getArrivalFloor());
    LOG(INFO) << "Elevator #" << elevatorNum
              << " will stop on floor " << client->getArrivalFloor()
              << " to pick up some clients.";
  }
}

void Building::updateElevators(const unsigned long time) {
  for (auto e : *_elevators) {
    assignDestinationForElevator(e);

    // Checks if elevator must stop at next floor.
    auto nextLocation = e->getNextLocation();

    if (_stops[e->getNumber()].find(nextLocation) != _stops[e->getNumber()].end()) {
      e->stopAtNextLocation();
      e->update();
      _stops[e->getNumber()].erase(nextLocation);

      auto passengersToDrop = e->dropPassengersToCurrentLocation();

      for (auto passenger : *passengersToDrop) {
        LOG(INFO) << "Elevator #" << e->getNumber()
                  << " dropped " << passenger->getPartySize()
                  << " clients at floor #" << e->getLocation() << ".";

        // TODO: Tá faltando uma coisinha ou outra aqui ainda
        auto stats = _simulator->getStatistics();
        stats->addTrip(time, e, passenger);
      }


      auto floor = _floors->at(e->getLocation());
      auto newStops = floor->boardElevator(e);

      for (auto stop : newStops) {
        _stops[e->getNumber()].insert(stop);
      }
    } else {
      e->update();
    }
  }
}

void Building::assignDestinationForElevator(const std::shared_ptr<Elevator> elevator) {
  const int number = elevator->getNumber();
  if (elevator->getStatus() == Status::Idle && !_stops[number].empty()) {
    // If a elevator is idle and has pending stops, then it should receive a new destination.
    if (elevator->getDirection() == Direction::Up) {
      // If it was going up, we send it down.
      elevator->setDestination(*_stops[number].begin());
    }
    else {
      // If it was going down, we send it up.
      elevator->setDestination(*_stops[number].rbegin());
    }
  }
}

