all: prog

prog: 2.5.o
	gcc 2.5.o -o prog

2.5.o: 2.5.c
	gcc -c 2.5.c

clean:
	rm -rf *.o prog