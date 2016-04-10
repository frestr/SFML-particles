CXX=g++
CPPFLAGS=-std=c++11 -c
LDFLAGS=-g
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system -lpthread

SRCS=main.cpp Particle.cpp ParticleManager.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: particle-app

particle-app: $(OBJS)
	$(CXX) -o particle-app $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(LDFLAGS) $(CPPFLAGS) $< 

clean:
	$(RM) $(OBJS)
