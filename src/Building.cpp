#include "Building.h"
#include "Client.h"
#include "ClientArrival.h"
#include "Clock.h"
#include "CostFunction.h"
#include "Direction.h"
#include "Scheduler.h"
#include "Elevator.h"
#include "EventFactory.h"
#include "Floor.h"
#include "Simulator.h"
#include "Statistics.h"
#include "Status.h"
#include "StopManager.h"
#include "Trip.h"
#include <algorithm>
#include <sstream>

Building::Building(
    std::shared_ptr<const Simulator> simulator, const std::shared_ptr<Clock> clock,
    std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
    std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
    std::shared_ptr<Scheduler> scheduler,
    std::shared_ptr<CostFunction> costFunction)
    : _simulator(simulator), _clock(clock), _floors(floors),
      _elevators(elevators), _scheduler(scheduler), _costFunction(costFunction),
      _stopManager(std::make_shared<StopManager>()) {}

Building::Building(const Building& building,
                   std::shared_ptr<const Simulator> simulator,
                   const std::shared_ptr<Clock> clock)
    : _simulator(simulator), _clock(clock),
      _floors(std::make_shared<std::vector<std::shared_ptr<Floor>>>()),
      _elevators(std::make_shared<std::vector<std::shared_ptr<Elevator>>>()),
      _scheduler(nullptr),    // acho que pode ficar nullptr
      _costFunction(nullptr), // acho que pode ficar nullptr
      _stopManager(std::make_shared<StopManager>(*building.getStopManager(), *building.getElevators()))
{
  for (auto floor : *building.getFloors()) {
    auto floorCopy = std::make_shared<Floor>(*floor);
    _floors->push_back(floorCopy);
  }

  for (auto elevator : *building.getElevators()) {
    auto elevatorCopy = std::make_shared<Elevator>(*elevator);
    _elevators->push_back(elevatorCopy);
  }
}

Building::~Building() {}

const std::shared_ptr<const Simulator> Building::getSimulator() const { return _simulator.lock(); }

const std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> Building::getElevators() const { return _elevators; }

const std::shared_ptr<std::vector<std::shared_ptr<Floor>>> Building::getFloors() const { return _floors; }

const std::shared_ptr<StopManager> Building::getStopManager() const { return _stopManager; }

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

void Building::step() {
  _clock->advanceBy(1);
  for (auto elevator : *_elevators) {
    updateElevator(elevator);
  }
}

void Building::setStop(const int destination, Direction direction, std::shared_ptr<Elevator> elevator) {
  auto floor = _floors->at(destination);
  _stopManager->set(floor, direction, elevator);
}

bool Building::mustStop(const int destination, Direction direction, std::shared_ptr<Elevator> elevator) {
  auto floor = _floors->at(destination);
  auto stops = _stopManager->getStops(elevator, direction);
  return stops.find(floor) != stops.end();
}

void Building::notify(const std::shared_ptr<const Event> event) {
  /*
    Ao ser notificado de um evento, o sistema deve atualizar o seu estado para
    refletir o que ocorreu no interim entre o momento do último evento
    processado e o evento que está sendo notificado.
  */

  for (int time = _clock->currentTime(); time < event->getTime(); ++time) {
    step();
  }

  /*
    Após a atualização do estado do sistema, o novo evento deve ser processado
    e o sistema deverá atualizar o seu estado de acordo com esse evento.
  */
  if (event->getType() == EventType::clientArrival) {
    doClientArrival(std::static_pointer_cast<const ClientArrival>(event));
  }

  if (event->getType() == EventType::finishSimulation) {
    auto simulator = _simulator.lock();
    auto statistics = simulator->getStatistics();
    while (statistics->getClientsArrived() > statistics->getClientsServed()) {
      _clock->advanceBy(1);
      for (auto elevator : *_elevators) {
        updateElevator(elevator);
      }
    }
  }
}

void Building::initializeArrivals() {
  auto simulator = _simulator.lock();
  auto eventQueue = simulator->getEventQueue();
  for (auto floor : *_floors)
    floor->createFutureArrival(eventQueue);
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

  if (!_stopManager->hasStop(location, direction)) {
    auto elevatorNum = _scheduler->schedule(_costFunction, shared_from_this(), client);
    auto elevator = _elevators->at(elevatorNum);
    _stopManager->set(location, direction, elevator);
  }

  auto simulator = _simulator.lock();
  auto eventQueue = simulator->getEventQueue();
  location->createFutureArrival(eventQueue);
}

void Building::updateElevator(const std::shared_ptr<Elevator> elevator) {
  if (elevator->getStatus() == Status::Idle) {
    elevator->setDestination(getDestinationForElevator(elevator));
  }

  elevator->move();
  if (mustStop(elevator)) {
    stop(elevator);

    auto droppedPassengers = elevator->dropPassengersToCurrentLocation();
    auto simulator = _simulator.lock();
    auto stats = simulator->getStatistics();
    stats->logDropOff(_clock->currentTime(), elevator, droppedPassengers);

    auto floor = _floors->at(elevator->getLocation());
    auto result = floor->boardElevator(_clock->currentTime(), elevator);
    registerNewStops(elevator, result.first);

    // se _scheduler for nullptr, não deverá reagendar
    // isso ocorre nos casos onde o planning faz cópias do simulator e do building
    // e não queremos entrar num loop infinito de scheduling
    if (result.second && _scheduler) {
      auto client = result.second;
      auto location = _floors->at(client->getArrivalFloor());
      auto direction = client->getDirection();

      if (!_stopManager->hasStop(location, direction)) {
        auto elevatorNum = _scheduler->schedule(_costFunction, shared_from_this(), client, elevator->getNumber());
        auto elevator = _elevators->at(elevatorNum);
        _stopManager->set(location, direction, elevator);
      }
    }
  }
}

std::pair<int, Direction> Building::getDestinationForElevator(const std::shared_ptr<Elevator> elevator) {
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
  auto direction = elevator->getDestination().second;
  _stopManager->clear(location, elevator, direction);
}

void Building::registerNewStops(std::shared_ptr<Elevator> elevator, std::set<int> stops) {
  for (auto floorNumber : stops) {
    auto location = _floors->at(elevator->getLocation());
    auto destination = _floors->at(floorNumber);
    _stopManager->set(destination, location->compareTo(*destination), elevator);

    if (elevator->getDirection() == Direction::Up && floorNumber > elevator->getDestination().first) {
      elevator->setDestination({floorNumber, Direction::Up});
    }
    else if (elevator->getDirection() == Direction::Down && floorNumber < elevator->getDestination().first) {
      elevator->setDestination({floorNumber, Direction::Down});
    }
  }
}
