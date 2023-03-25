all: lab06

lab06: lab06.o cobra.o
	gcc lab06.o cobra.o -lm -o lab06

lab06.o: lab06.c cobra.h
	gcc -std=c99 -Wall -Werror -c lab06.c

cobra.o: cobra.c cobra.h
	gcc -std=c99 -Wall -Werror -c cobra.c