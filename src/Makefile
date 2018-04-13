CXX = g++
CXXFLAGS = -std=c++11 -O3 -march=native -DNDEBUG
#CXXFLAGS = -std=c++11 -O0 -g
OBJFILES = partition.o \
	vertex.o \
	index.o \
	algorithms.o

all: edp_test edp_main

edp_test: $(OBJFILES) edp_test.o
	$(CXX) $(CXXFLAGS) -o $@ $^

edp_main: $(OBJFILES) edp_main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY:
clean:
	rm -f *.o edp
