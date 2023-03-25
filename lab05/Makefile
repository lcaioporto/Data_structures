all: lab05

lab05: lab05.o ultron.o
	gcc lab05.o ultron.o -lm -o lab05

lab05.o: lab05.c ultron.h
	gcc -std=c99 -Wall -Werror -c lab05.c

ultron.o: ultron.c ultron.h
	gcc -std=c99 -Wall -Werror -c ultron.c