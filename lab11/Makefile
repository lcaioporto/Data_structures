all: lab11

lab11: lab11.o grafo.o
	gcc lab11.o grafo.o -lm -o lab11

lab11.o: lab11.c grafo.h
	gcc -std=c99 -Wall -Werror -c lab11.c

grafo.o: grafo.c grafo.h
	gcc -std=c99 -Wall -Werror -c grafo.c

clean:
	rm -f grafo.o lab11.o