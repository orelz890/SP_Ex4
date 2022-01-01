FLAGS=-g -Wall

all: graph
graph: main.c graph.c graph.h
	gcc $(FLAGS) main.c graph.c -o graph

.PHONY: clean all
clean:
	rm -f *.o *.a graph