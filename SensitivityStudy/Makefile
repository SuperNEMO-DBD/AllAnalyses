
CC=g++
INCLUDES      = 
CFLAGS=-c -g -Wall `root-config --cflags`
LDFLAGS=`root-config --glibs`
OBJECTS=$(SOURCES:.cc=.o)

# make a binary for every .cxx file
all : $(patsubst %.cxx, %.o, $(wildcard *.cxx))

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cxx $(INCLUDES)
	$(CC) ${CFLAGS} -o $@ $<

clean:
	rm -f $(wildcard *.o) $(patsubst %.cxx, %, $(wildcard *.cxx))

