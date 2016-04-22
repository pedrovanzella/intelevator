cmake_minimum_required(VERSION 3.3)
project(intelevator)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/BetterNearestNeighbourDispatcher.cpp
        src/ClientArrival.cpp
        src/DummyDispatcher.cpp
        src/Event.cpp
        src/EventFactory.cpp
        src/NearestNeighbourCostFunction.cpp
        src/Simulator.cpp
        src/main.cpp
        src/Building.cpp
        src/Clock.cpp
        src/Elevator.cpp
        src/EventComparator.cpp
        src/EventQueue.cpp
        src/NearestNeighbourDispatcher.cpp
        src/Statistics.cpp
        src/Client.cpp
        src/DummyCostFunction.cpp
        src/ElevatorArrival.cpp
        src/EventDispatcher.cpp
        src/Floor.cpp
        src/Scenario.cpp
        src/RandomDispatcher.cpp
        src/Trip.cpp)

set(TEST_FILES
        src/BetterNearestNeighbourDispatcher.cpp
        src/ClientArrival.cpp
        src/DummyDispatcher.cpp
        src/Event.cpp
        src/EventFactory.cpp
        src/NearestNeighbourCostFunction.cpp
        src/Simulator.cpp
        src/Building.cpp
        src/Clock.cpp
        src/Elevator.cpp
        src/EventComparator.cpp
        src/EventQueue.cpp
        src/NearestNeighbourDispatcher.cpp
        src/Statistics.cpp
        src/Client.cpp
        src/DummyCostFunction.cpp
        src/ElevatorArrival.cpp
        src/EventDispatcher.cpp
        src/Floor.cpp
        src/Scenario.cpp
        src/Trip.cpp
        src/RandomDispatcher.cpp
        test/BuildingTest.cpp
        test/ClientArrivalTest.cpp
        test/ClientTest.cpp
        test/ClockTest.cpp
        test/ElevatorTest.cpp
        test/EventQueueTest.cpp
        test/FloorTest.cpp)


include_directories(include ${GLOG_INCLUDE_DIRS})

add_executable(intelevator ${SOURCE_FILES})
add_executable(intelevatorTests ${TEST_FILES})

target_link_libraries(intelevatorTests gtest gtest_main)
target_link_libraries(intelevatorTests yaml-cpp)
target_link_libraries(intelevator yaml-cpp)
target_link_libraries(intelevatorTests glog)
target_link_libraries(intelevator glog)


add_test(intelevatorTests intelevatorTests)

install(TARGETS intelevator DESTINATION bin)
install(TARGETS intelevatorTests DESTINATION bin)
install(FILES ../config.yaml ../test_config.yaml DESTINATION bin)