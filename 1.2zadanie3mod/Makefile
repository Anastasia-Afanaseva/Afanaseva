all: prog

prog: 1.2.o
	gcc 1.2.o -o prog

1.2.o: 1.2.c
	gcc -c 1.2.c

clean:
	rm -rf *.o prog