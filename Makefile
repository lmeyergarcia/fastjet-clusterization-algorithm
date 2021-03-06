ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) -lMLP -lTreePlayer -lMinuit
ROOTGLIBS     = $(shell root-config --glibs)
FASTJET       = $(shell /usr/local/share/fastjet-3.1.3/bin/fastjet-config --cxxflags --libs --plugins)

CXX           = g++
CXXFLAGS      = -g -I$(ROOTSYS)/include -O -Wall -fPIC
LD            = g++
SOFLAGS       = -shared


CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS)
GLIBS         = $(ROOTGLIBS)

all: fastjet_clustering.exe

fastjet_clustering.exe: FastJet_tracks.cpp 
	$(CXX) -rdynamic -o fastjet_clustering.exe $(ROOTLIBS) $(ROOTCFLAGS) $(FASTJET) -ldl -g $<


clean:
	rm -f *.o *.exe


