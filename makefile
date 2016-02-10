CPP=clang++
CXXFLAGS=-Wall -Werror -Wpedantic -std=c++11

all: intelevator

intelevator: main.o event.o client.o elevator.o eventtype.o floor.o config.o building.o direction.o timer.o trip.o
	$(CPP) $^ -o $@

main.o: main.cpp
	$(CPP) $(CXXFLAGS) -c main.cpp

building.o: building.cpp building.h
	$(CPP) $(CXXFLAGS) -c building.cpp

config.o: config.cpp config.h
	$(CPP) $(CXXFLAGS) -c config.cpp

client.o: client.cpp client.h
	$(CPP) $(CXXFLAGS) -c client.cpp

direction.o: direction.cpp direction.h
	$(CPP) $(CXXFLAGS) -c direction.cpp

elevator.o: elevator.cpp elevator.h
	$(CPP) $(CXXFLAGS) -c elevator.cpp

event.o: event.cpp event.h
	$(CPP) $(CXXFLAGS) -c event.cpp

eventtype.o: eventtype.cpp eventtype.h
	$(CPP) $(CXXFLAGS) -c eventtype.cpp

floor.o: floor.cpp floor.h
	$(CPP) $(CXXFLAGS) -c floor.cpp

timer.o: timer.cpp timer.h
	$(CPP) $(CXXFLAGS) -c timer.cpp

trip.o: trip.cpp trip.h
	$(CPP) $(CXXFLAGS) -c trip.cpp

clean:
	rm -rf ./*.o intelevator
