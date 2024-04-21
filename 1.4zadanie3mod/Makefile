all: prog

prog: 1.4.o
	gcc 1.4.o -o prog

1.4.o: 1.4.c
	gcc -c 1.4.c

clean:
	rm -rf *.o prog

