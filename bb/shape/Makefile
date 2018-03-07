CXX = clang++

# Warnings frequently signal eventual errors:
CXXFLAGS= -g -std=c++11 -W -Wall -Weffc++ -Wextra -pedantic -O0

OBJS = \
        shape.o
EXEC = run

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

shape.o: shape.cpp

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
