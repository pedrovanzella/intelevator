cmake_minimum_required(VERSION 3.3)
project(intelevator)

include_directories(include ${gtest_SOURCE_DIR}/include $gtest_SOURCE_DIR})

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


add_executable(intelevator ${SOURCE_FILES})
add_executable(intelevatorTests ${SOURCE_FILES})

target_link_libraries(intelevatorTests gtest gtest_main)