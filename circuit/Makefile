
# use g++47
CC = g++-4.7

GCCDIR = /usr/local/gcc47/gcc-4.7
CPP_INCLUDE_PATH = -I $(GCCDIR)/include
CPP_LIBRARY_PATH = -L $(GCCDIR)/lib

INCLUDE_PATH = -I ./ -I ../

CFLAGS = -std=c++0x $(INCLUDE_PATH) $(CPP_INCLUDE_PATH)
LFLAGS = -std=c++0x $(CPP_LIBRARY_PATH)

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
	