#pragma once

#include <memory>
#include <queue>
#include <set>

class Client;         // forward declaration
enum class Direction; // forward declaration
class Elevator;       // forward declaration
class EventFactory;   // forward declaration
class EventQueue;     // forward declaration
class Simulator;      // forward declaration

class Floor {
public:
  Floor(const int number, const float lambda);
  Floor(const Floor& floor);
  virtual ~Floor();

  int getNumber() const;
  int getLambda() const;
  std::queue<std::shared_ptr<Client>> getUpLine() const;
  std::queue<std::shared_ptr<Client>> getDownLine() const;
  const std::vector<std::shared_ptr<Client>> getUpLine(int n) const;
  const std::vector<std::shared_ptr<Client>> getDownLine(int n) const;
  int clientsOnUpLine() const;
  int clientsOnDownLine() const;
  Direction compareTo(const Floor &other) const;

  void setEventFactory(const std::shared_ptr<EventFactory> eventFactory);
  Direction addClient(const std::shared_ptr<Client> client);
  std::pair<std::set<int>, std::shared_ptr<Client>> boardElevator(const unsigned long time, std::shared_ptr<Elevator> elevator);

  void createFutureArrival(const std::shared_ptr<EventQueue> eventQueue);

  std::string str() const;
  static std::shared_ptr<std::vector<std::shared_ptr<Floor>>> create(const std::shared_ptr<const Simulator> simulator);

private:
  int _number;
  int _lambda;
  std::queue<std::shared_ptr<Client>> _upLine;
  std::queue<std::shared_ptr<Client>> _downLine;
  std::shared_ptr<EventFactory> _eventFactory;
};
