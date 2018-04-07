CXX = g++
CXXFLAGS = -std=c++11 -O3 -march=native
OBJFILES = partition.o \
	vertex.o \
	edp.o

all: $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o edp $^

.PHONY:
clean:
	rm -f *.o edp
