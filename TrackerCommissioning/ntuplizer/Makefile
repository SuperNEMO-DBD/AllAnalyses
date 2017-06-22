objects = Unpack.o rawkeys.o GeigerEvent.o RawGeigerHit.o \
	UnpackingErrors.o DriftModel.o

objdisp = EventViewer.o ViewerGui.o ViewerGuiDict.o

CXXFLAGS=-I. $(shell root-config --cflags)

rootflags =$(shell root-config --glibs --cflags)

all: clean ctest evdisp plotraw hackraw

ViewerGuiDict.cc:
	rootcint -f ViewerGuiDict.cc -c ViewerGui.h  \
	ViewerGuiLinkDef.h

ctest: $(objects) ctest.o
	g++ -o ctest ctest.o $(objects)

evdisp: $(objects) $(objdisp) evdisp.o
	g++ -o evdisp evdisp.o $(objects) $(objdisp) $(rootflags)

plotraw: $(objects) plotraw.o
	g++ -o plotraw plotraw.o $(objects) $(rootflags)

.PHONY: clean
clean :
	rm -f ctest evdisp plotraw $(objects) $(objdisp)
	rm -f ctest.o evdisp.o plotraw.o
	rm -f ViewerGuiDict.cc ViewerGuiDict.h
