CC=gcc
AR=ar
FLAGS=-g -Wall

all: graph prog

prog: main.o graph.a
	$(CC) $(FLAGS) -o prog main.o graph.a

graph: graph.a
graph.a: graph.o
	$(AR) -rcs -o graph.a graph.o

graph.o: graph.c graph.h
	$(CC) $(FLAGS) -c graph.c

main.o: main.c graph.h
	$(CC) $(FLAGS) -c main.c

.PHONY: clean all
clean:
	rm -f *.o *.a prog
