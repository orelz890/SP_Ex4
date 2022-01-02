FLAGS=-g -Wall

all: graph
graph: main.c graph.c priorityQueue.c  priorityQueue.h graph.h
	gcc $(FLAGS) main.c graph.c priorityQueue.c -o graph

.PHONY: clean all
clean:
	rm -f *.o *.a graph