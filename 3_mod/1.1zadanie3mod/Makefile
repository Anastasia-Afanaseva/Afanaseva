all: prog

prog: 1.1.o
	gcc 1.1.o -o prog

1.1.o: 1.1.c
	gcc -c 1.1.c

clean:
	rm -rf *.o prog