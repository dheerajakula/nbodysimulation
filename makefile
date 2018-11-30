CC=gcc
CXX=g++
RM=rm -f
OBJS=nbody.cpp
LDLIBS = 


src = $(OBJS)
obj = $(src:.cpp=.o)

.PHONY: all run clean

all: run

finalbinary: $(obj)
	$(CXX) -o finalbinary $^ $(LDLIBS)

run:finalbinary
	./finalbinary init.txt

clean:
	rm -f $(obj) finalbinary

