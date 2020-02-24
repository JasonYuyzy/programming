all: gameoflife.o libgol.o gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife gameoflife.o gol.o

libgol.o: gol.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -c gol.c

gameoflife.o: gameoflife.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -c gameoflife.c

clean:
	rm -rf gameoflife gameoflife.o libgol.o

