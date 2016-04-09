#include "Building.h"
#include "Elevator.h"
#include "Floor.h"
#include <algorithm>
#include <glog/logging.h>
#include <sstream>

Building::Building(
  std::shared_ptr<std::vector<std::shared_ptr<Floor>>> floors,
  std::shared_ptr<std::vector<std::shared_ptr<Elevator>>> elevators,
  std::shared_ptr<const Dispatcher> dispatcher,
  std::shared_ptr<const CostFunction> costFunction)
  : _floors(floors), _elevators(elevators), _dispatcher(dispatcher),
    _costFunction(costFunction), _stops(), _lastEventTime(0) {

  initializeStops();
}

Building::~Building() {}

void Building::notify(const std::shared_ptr<const Event> event) {
  for (int time = _lastEventTime; time < event->getTime(); ++time) {
    updateElevators();
  }

  if (event->getType() == EventType::clientArrival) {
    doClientArrival(std::static_pointer_cast<const ClientArrival>(event));
  }
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

std::string Building::stopsToString() const
{
  std::ostringstream stream;
  stream << "\n";

  for (auto el : _stops) {
    stream << "Elevator #" << el.first << " stops: [ ";

    for (auto b : el.second)
      stream << b << " ";

    stream << "]\n";
  }

  return stream.str();
}

void Building::initializeStops() {
  for (auto e : *_elevators) {
    std::vector<bool> stops(_floors->size());

    for (auto f : *_floors)
      stops[f->getNumber()] = false;

    _stops[e->getNumber()] = stops;
  }
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

  auto location = _floors->at(event->getLocation());
  location->addClient(event->getClient());

  /*
    O sistema, ao perceber que um novo botão foi pressionado, designa um
    elevador para atender aquela nova requisição.
  */

  int elevatorNum = _dispatcher->pick_next_elevator(_costFunction, shared_from_this(), event);

  /* Agora, esse elevador deve parar no andar em que ocorreu o evento para buscar a pessoa. */
  if (!_stops[elevatorNum][event->getLocation()]) {
    _stops[elevatorNum][event->getLocation()] = true;
    LOG(INFO) << "Elevator #" << elevatorNum << " will stop on floor " << event->getLocation() << " to pick up some clients.";
  }
}

void Building::updateElevators() {
  for (auto e : *_elevators) {

    // Checks if elevator must stop at next floor.
    auto nextLocation = e->getNextLocation();
    bool shouldStop = _stops[e->getNumber()][nextLocation];

    if (shouldStop) e->stopAtNextLocation();

    e->update();

    if (shouldStop) _stops[e->getNumber()][nextLocation] = false;

    /* Neste ponto, se o elevador estiver parado, é por que ele deveria estar. :P
       Assim, as pessoas que querem descer neste andar devem sair e as pessoas que
       irão embarcar no elevador devem entrar. */

    if (e->getStatus() == Status::Stopped) {
      auto dropped = e->dropPassengersToCurrentLocation();

      LOG_IF(INFO, !dropped->empty())
        << "Elevator #" << e->getNumber()
        << " dropped " << dropped->size()
        << " clients at floor #" << e->getLocation() << ".";

      if (e->getDirection() == Direction::Up) {
        /* Embarcar as pessoas que irão subir com o elevador. */
      }
      else if (e->getDirection() == Direction::Down) {
        /* Embarcar as pessoas que irão descer com o elevador. */
      }
    }
  }
}
