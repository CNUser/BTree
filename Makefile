CXX=g++
OBJS=BTree.o main.o

all: main

main: $(OBJS)
	$(CXX) -o main $(OBJS)
	
BTree.o: BTree.cpp BTree.h
	$(CXX) -c BTree.cpp	

main.o: main.cpp BTree.h
	$(CXX) -c main.cpp
	
clean:
	rm main $(OBJS)
	
.PHONY: clean