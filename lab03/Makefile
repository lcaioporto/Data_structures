all: lab03

lab03: lab03.o represa.o
	gcc lab03.o represa.o -lm -o lab03

lab03.o: lab03.c represa.h
	gcc -std=c99 -Wall -Werror -c lab03.c

represa.o: represa.c represa.h
	gcc -std=c99 -Wall -Werror -c represa.c