CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS= 
LDLIBS= -lboost_filesystem -lboost_system
SOURCES=src/getch.cpp src/Serial_Connect.cpp src/serialWrite.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=send_command

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	$(RM) *.o *~  $(EXECUTABLE) 
