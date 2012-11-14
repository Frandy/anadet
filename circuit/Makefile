
CC = g++

INCLUDE_PATH = -I ./ -I ../

CFLAGS = -std=c++0x $(INCLUDE_PATH)
LFLAGS = -std=c++0x

HEADERS = elem.h \
		std.hpp

SOURCES = test_circuit.cpp

OBJECTS = $(SOURCES:.cpp=.o)

.cpp.o:
	$(CC) -c $< -o $@ $(CFLAGS) 

TARGET = test_circuit

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) $^ -o $@ $(LFLAGS)
	
clean:
	rm -rf $(OBJECTS)	
	