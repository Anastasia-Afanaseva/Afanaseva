all: prog

prog: 2.8.o
	gcc 2.8.o -o prog

2.8.o: 2.8.c
	gcc -c 2.8.c

clean:
	rm -rf *.o prog