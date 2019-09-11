OBJECTS = main.cpp mock/mocker.cpp test/tester.cpp
STD = -std=c++17
MYFLAGS = -g -Wall
CXX = g++
EXEC = main

all: $(OBJECTS)
	$(CXX) $(STD) $(MYFLAGS) $(OBJECTS) -o $(EXEC)

clean: 
	rm $(EXEC)

