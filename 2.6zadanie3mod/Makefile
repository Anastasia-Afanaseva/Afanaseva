all: prog

prog: 2.6.o
	gcc 2.6.o -o prog

2.6.o: 2.6.c
	gcc -c 2.6.c

clean:
	rm -rf *.o prog