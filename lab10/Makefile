all: lab10

lab10: lab10.o hash.o
	gcc lab10.o hash.o -lm -o lab10

lab10.o: lab10.c hash.h
	gcc -std=c99 -Wall -Werror -c lab10.c

hash.o: hash.c hash.h
	gcc -std=c99 -Wall -Werror -c hash.c

clean:
	rm -f hash.o lab10.o