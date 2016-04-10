CXX=g++
CPPFLAGS=-std=c++11 -c
LDFLAGS=
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lpthread

SRCS=$(wildcard src/*.cpp)
OBJS=$(notdir $(SRCS:.cpp=.o))

all: particle-app

particle-app: $(OBJS)
	$(CXX) -o particle-app $(OBJS) $(LDLIBS)

%.o: src/%.cpp
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $< 

clean:
	$(RM) $(OBJS)
