all: gameoflife.o libgol.so gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife gameoflife.o libgol.so

libgol.so: gol.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -o libgol.so -c gol.c

gameoflife.o: gameoflife.c gol.h
	gcc -Wall -Wextra -pedantic -std=c11 -c gameoflife.c

clean:
	rm -rf gameoflife gameoflife.o libgol.so

