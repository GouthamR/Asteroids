CXX=g++
CXXFLAGS=-c -Wall -std=c++11
INCLUDES=-I../SFML-2.1/include
LDFLAGS=-L../SFML-2.1/lib
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	cp ../SFML-2.1/bin/*.dll ./
	./$(EXECUTABLE)
	rm *.dll