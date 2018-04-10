CXX = g++
#CXXFLAGS = -std=c++11 -O3 -march=native
CXXFLAGS = -std=c++11 -O0 -g
OBJFILES = partition.o \
	vertex.o \
	index.o \
	edp.o

all: $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o edp $^

.PHONY:
clean:
	rm -f *.o edp
