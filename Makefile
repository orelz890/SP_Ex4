FLAGS=-g -Wall

all: graph
graph: main.c graph.c priorityQueue.c List.c priorityQueue.h graph.h List.h
	gcc $(FLAGS) main.c graph.c priorityQueue.c List.c -o graph

.PHONY: clean all
clean:
	rm -f *.o graph