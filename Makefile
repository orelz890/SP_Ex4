FLAGS=-g -Wall

all: graph
graph: graph.o
graph.o: main.c graph.c graph.h
	gcc $(FLAGS) main.c graph.c -o graph.o

.PHONY: clean all
clean:
	rm -f *.o *.a graph