all: prog

prog: 2.2.o
	gcc 2.2.o -o prog

2.2.o: 2.2.c
	gcc -c 2.2.c

clean:
	rm -rf *.o prog