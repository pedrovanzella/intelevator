CPP=clang++
CXXFLAGS=-Wall -Werror -Wpedantic

all: intelevator

intelevator: main.o
	$(CPP) main.o -o intelevator

main.o: main.cpp
	$(CPP) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf ./*.o intelevator
