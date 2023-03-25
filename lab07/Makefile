lab07: lab07.o pilha.o fila.o
	gcc lab07.o pilha.o fila.o -lm -o lab07

lab07.o: lab07.c pilha.h fila.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c lab07.c

pilha.o: pilha.c pilha.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c pilha.c

fila.o: fila.c fila.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c fila.c

clean:
	rm -f pilha.o fila.o lab07.o