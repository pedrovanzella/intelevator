cmake_minimum_required(VERSION 3.3)
project(intelevator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/Building.cpp
    src/Client.cpp
    src/ClientArrival.cpp
    src/Clock.cpp
    src/Config.cpp
    src/Elevator.cpp
    src/ElevatorArrival.cpp
    src/Event.cpp
    src/EventComparator.cpp
    src/EventDispatcher.cpp
    src/EventQueue.cpp
    src/Floor.cpp
    src/main.cpp
    src/Simulator.cpp
    src/Statistics.cpp
    src/Trip.cpp)

include_directories(include)

add_executable(intelevator ${SOURCE_FILES})