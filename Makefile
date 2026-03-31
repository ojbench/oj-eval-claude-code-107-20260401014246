CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

code: solution.cpp
	$(CXX) $(CXXFLAGS) -o code solution.cpp

clean:
	rm -f code *.o

.PHONY: clean
