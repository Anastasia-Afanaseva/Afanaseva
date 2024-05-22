all: prog

prog: 2.7.o
	gcc 2.7.o -o prog

2.7.o: 2.7.c
	gcc -c 2.7.c

clean:
	rm -rf *.o prog