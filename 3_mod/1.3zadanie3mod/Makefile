all: prog

prog: 1.3.o
	gcc 1.3.o -o prog

1.3.o: 1.3.c
	gcc -c 1.3.c

clean:
	rm -rf *.o prog

